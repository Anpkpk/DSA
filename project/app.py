import sys
import tkinter as tk
import csv, time
from tkinter import filedialog, messagebox
import re, math, mmh3
import math
from collections import Counter
from bitarray import bitarray

csv.field_size_limit(10 * 1024 * 1024)  # 10MB / field


# ================= BLOOM FILTER =================

class BloomFilter:
    def __init__(self, n, p=0.01):
        self.m = int(-(n * math.log(p)) / (math.log(2) ** 2))
        self.k = int((self.m / n) * math.log(2))
        self.bits = bitarray(self.m)
        self.bits.setall(0)

    def add(self, item):
        for i in range(self.k):
            self.bits[mmh3.hash(item, i) % self.m] = 1

    def contains(self, item):
        for i in range(self.k):
            if not self.bits[mmh3.hash(item, i) % self.m]:
                return False
        return True

# ================= SPAM INDICATORS =================

SPAM_KEYWORDS = [
    "win money", "won money", "cash", "prize", "claim prize",
    "lottery", "winner", "jackpot", "million dollars",
    "financial freedom", "instant cash", "easy money",
    "get rich", "earn money fast", "free offer", "limited offer", 
    "special promotion", "act now", "order now", "buy now",
    "free trial", "100% free", "no cost", "discount", 
    "cheap price", "click here", "verify your account", 
    "confirm your account", "login immediately", "winner"
    "security alert", "unusual activity", "update your information",
    "account suspended",  "dear friend", "dear customer", "dear user",
    "this is not spam", "urgent message", "reply immediately", 
    "attention required", "casino", "online betting", "poker",
    "viagra", "cialis", "weight loss", "congratulations",
    "lose weight fast", "miracle cure", "immediately"
]


SPAM_SENDERS = [
    "promo@", "lottery@", "reward@", "noreply@",
    "winner@", "support@security"
]

SUSPICIOUS_DOMAINS = [
    ".ru", ".xyz", ".top", ".click",
    "freegift.com", "claim-now.com",
    "secure-login.net", "verify-account.org"
]


INDICATORS = SPAM_KEYWORDS + SPAM_SENDERS + SUSPICIOUS_DOMAINS

bf = BloomFilter(len(INDICATORS))
for x in INDICATORS:
    bf.add(x)

# ================= FEATURE EXTRACTION =================

def extract_features(text):
    features = []

    sender = re.search(r'From:\s*(\S+)', text, re.I)
    if sender:
        email = sender.group(1).lower()
        features.append(email)
        features.append(email.split("@")[-1])

    subject = re.search(r'Subject:\s*(.*)', text, re.I)
    if subject:
        s = subject.group(1).lower()
        for k in SPAM_KEYWORDS:
            if k in s:
                features.append(k)

    body = text.lower()
    for k in SPAM_KEYWORDS + SUSPICIOUS_DOMAINS:
        if k in body:
            features.append(k)

    return features

def is_gibberish(text):
    non_alpha = sum(not c.isalpha() for c in text)
    return non_alpha / max(len(text), 1) > 0.4

def entropy(text):
    freq = Counter(text)
    return -sum((c/len(text)) * math.log2(c/len(text)) for c in freq.values())


# ================= STATS =================

false_positive = 0
total_ham = 0

def evaluate_csv(path):
    start = time.time()

    total = correct = 0
    fp = ham_count = 0
    threshold = slider.get()

    with open(path, newline='', encoding="utf-8", errors="ignore") as f:
        reader = csv.DictReader(f)
        for row in reader:
            subject = row["Subject"]
            message = row["Message"]
            label = row["Spam/Ham"].lower().strip()

            text = f"Subject: {subject}\n{message}"

            features = extract_features(text)
            matches = sum(bf.contains(f) for f in features)
            pred_spam = matches >= threshold

            true_spam = label == "spam"

            total += 1
            if pred_spam == true_spam:
                correct += 1

            if not true_spam:
                ham_count += 1
                if pred_spam:
                    fp += 1

    acc = correct / total if total else 0
    fpr = fp / ham_count if ham_count else 0
    elapsed = time.time() - start

    return total, acc, fpr, elapsed

def open_csv_and_evaluate():
    path = filedialog.askopenfilename(filetypes=[("CSV files", "*.csv")])
    if not path:
        return

    total, acc, fpr, t = evaluate_csv(path)

    lbl_stats.config(
        text=(
            f"CSV Evaluation\n"
            f"-----------------\n"
            f"Total emails: {total}\n"
            f"Accuracy: {acc:.2f}\n"
            f"False Positive Rate: {fpr:.2f}\n"
            f"Time: {t:.2f} s"
        )
    )


# ================= GUI =================

def open_file():
    path = filedialog.askopenfilename(filetypes=[("Text files", "*.txt")])
    if not path:
        return
    with open(path, "r", encoding="utf-8", errors="ignore") as f:
        email_textbox.delete("1.0", tk.END)
        email_textbox.insert(tk.END, f.read())

def check_email():
    global false_positive, total_ham

    email_text = email_textbox.get("1.0", tk.END)
    threshold = slider.get()

    features = extract_features(email_text)
    matches = sum(bf.contains(f) for f in features)
    if is_gibberish(email_text): 
        matches += 2
    if entropy(email_text) > threshold: 
        matches += 1

    result = "SPAM" if matches >= threshold else "HAM"
    color = "red" if result == "SPAM" else "green"
    lbl_result.config(
        text=f"Result: {result}\nMatches: {matches}",
        fg=color
    )

    if is_ham.get():
        total_ham += 1
        if result == "SPAM":
            false_positive += 1

    update_stats()

def update_stats():
    fpr = (false_positive / total_ham) if total_ham else 0
    lbl_stats.config(
        text=f"HAM tested: {total_ham}\nFalse Positive: {false_positive}\nFPR: {fpr:.2f}"
    )

# ================= WINDOW =================

root = tk.Tk()
root.title("Bloom Filter Spam Detection Demo")
root.geometry("900x550")
root.configure(bg="#f2f2f2")

# ===== MAIN LAYOUT =====
main_frame = tk.Frame(root, bg="#f2f2f2")
main_frame.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)

left_frame = tk.Frame(main_frame, width=250, bg="#e6e6e6")
left_frame.pack(side=tk.LEFT, fill=tk.Y, padx=5)

right_frame = tk.Frame(main_frame, bg="white")
right_frame.pack(side=tk.RIGHT, fill=tk.BOTH, expand=True, padx=5)

# ===== LEFT PANEL =====
tk.Label(
    left_frame, text="Controls",
    font=("Arial", 14, "bold"),
    bg="#e6e6e6"
).pack(pady=10)

tk.Button(
    left_frame, text="📂 Open Email (.txt)",
    command=open_file,
    width=20
).pack(pady=5)

tk.Button(
    left_frame, text="📊 Evaluate CSV (Enron)",
    command=open_csv_and_evaluate,
    width=20
).pack(pady=5)


tk.Label(left_frame, text="Threshold", bg="#e6e6e6").pack(pady=(15, 0))

slider = tk.Scale(
    left_frame, from_=1, to=8,
    orient=tk.HORIZONTAL, length=180
)
slider.set(2)
slider.pack()

is_ham = tk.BooleanVar()
tk.Checkbutton(
    left_frame, text="This email is HAM",
    variable=is_ham,
    bg="#e6e6e6"
).pack(pady=10)

tk.Button(
    left_frame, text="🚀 Check Spam",
    command=check_email,
    width=20
).pack(pady=10)

tk.Label(
    left_frame, text="Statistics",
    font=("Arial", 12, "bold"),
    bg="#e6e6e6"
).pack(pady=(20, 5))

lbl_stats = tk.Label(
    left_frame,
    text="No CSV loaded",
    bg="#e6e6e6",
    justify=tk.LEFT
)

lbl_stats.pack()

# ===== RIGHT PANEL =====
tk.Label(
    right_frame, text="Email Content",
    font=("Arial", 14, "bold"),
    bg="white"
).pack(anchor="w", padx=10, pady=5)

email_textbox = tk.Text(
    right_frame, wrap=tk.WORD,
    font=("Consolas", 11)
)
email_textbox.pack(fill=tk.BOTH, expand=True, padx=10, pady=5)

lbl_result = tk.Label(
    right_frame,
    text="Result: ---",
    font=("Arial", 16, "bold"),
    bg="white"
)
lbl_result.pack(pady=10)

root.mainloop()