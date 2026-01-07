import sys
import tkinter as tk
import csv, time
from tkinter import filedialog, messagebox
import re, math, mmh3
import math
from collections import Counter
from bitarray import bitarray

csv.field_size_limit(10 * 1024 * 1024)  # 10MB / field

BG_MAIN   = "#f5f7fa"   
BG_LEFT   = "#eef1f6"   
BG_RIGHT  = "#ffffff"  
BTN_COLOR = "#4f46e5" 
BTN_HOVER = "#4338ca"
TEXT_MAIN = "#111827"
TEXT_SUB  = "#374151"
BORDER    = "#d1d5db"
SUCCESS   = "#16a34a"
ERROR     = "#dc2626"


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
root.geometry("1000x600")
root.configure(bg=BG_MAIN)

main_frame = tk.Frame(root, bg=BG_MAIN)
main_frame.pack(fill=tk.BOTH, expand=True, padx=12, pady=12)

left_frame = tk.Frame(
    main_frame, width=260,
    bg=BG_LEFT, highlightbackground=BORDER, highlightthickness=1
)
left_frame.pack(side=tk.LEFT, fill=tk.Y, padx=(0, 10))

right_frame = tk.Frame(
    main_frame, bg=BG_RIGHT,
    highlightbackground=BORDER, highlightthickness=1
)
right_frame.pack(side=tk.RIGHT, fill=tk.BOTH, expand=True)


def styled_button(parent, text, command):
    btn = tk.Button(
        parent, text=text,
        command=command,
        bg=BTN_COLOR, fg="white",
        font=("Segoe UI", 10, "bold"),
        activebackground=BTN_HOVER,
        activeforeground="white",
        relief=tk.FLAT,
        padx=10, pady=6,
        cursor="hand2"
    )
    btn.bind("<Enter>", lambda e: btn.config(bg=BTN_HOVER))
    btn.bind("<Leave>", lambda e: btn.config(bg=BTN_COLOR))
    return btn

# ===== LEFT PANEL =====
tk.Label(
    left_frame, text="⚙ Controls",
    font=("Segoe UI", 14, "bold"),
    bg=BG_LEFT, fg=TEXT_MAIN
).pack(pady=(12, 16))

styled_button(left_frame, "📂 Open Email (.txt)", open_file).pack(pady=6, fill=tk.X, padx=12)
styled_button(left_frame, "📊 Evaluate CSV (Enron)", open_csv_and_evaluate).pack(pady=6, fill=tk.X, padx=12)

tk.Label(
    left_frame, text="Threshold",
    bg=BG_LEFT, fg=TEXT_SUB,
    font=("Segoe UI", 10, "bold")
).pack(pady=(20, 5))

slider = tk.Scale(
    left_frame, from_=1, to=8,
    orient=tk.HORIZONTAL,
    bg=BG_LEFT, fg=TEXT_MAIN,
    troughcolor="#dbeafe",
    highlightthickness=0
)
slider.set(2)
slider.pack(padx=12, fill=tk.X)

is_ham = tk.BooleanVar()
tk.Checkbutton(
    left_frame,
    text="This email is HAM",
    variable=is_ham,
    bg=BG_LEFT,
    fg=TEXT_MAIN,
    activebackground=BG_LEFT,
    font=("Segoe UI", 10)
).pack(pady=10)

styled_button(left_frame, "🚀 Check Spam", check_email).pack(pady=12, fill=tk.X, padx=12)


tk.Label(
    left_frame, text="📈 Statistics",
    font=("Segoe UI", 12, "bold"),
    bg=BG_LEFT, fg=TEXT_MAIN
).pack(pady=(20, 5))

lbl_stats = tk.Label(
    left_frame,
    text="No CSV loaded",
    bg=BG_LEFT,
    fg=TEXT_SUB,
    justify=tk.LEFT,
    font=("Consolas", 9)
)
lbl_stats.pack(padx=12, anchor="w")


# ===== RIGHT PANEL =====
tk.Label(
    right_frame, text="📧 Email Content",
    font=("Segoe UI", 14, "bold"),
    bg=BG_RIGHT, fg=TEXT_MAIN
).pack(anchor="w", padx=12, pady=(10, 5))

email_textbox = tk.Text(
    right_frame,
    wrap=tk.WORD,
    font=("Consolas", 11),
    relief=tk.FLAT,
    highlightbackground=BORDER,
    highlightthickness=1
)
email_textbox.pack(fill=tk.BOTH, expand=True, padx=12, pady=5)

lbl_result = tk.Label(
    right_frame,
    text="Result: ---",
    font=("Segoe UI", 16, "bold"),
    bg=BG_RIGHT,
    fg=TEXT_MAIN
)
lbl_result.pack(pady=12)

root.mainloop()