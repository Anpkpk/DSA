import sys
import tkinter as tk
from tkinter import filedialog, messagebox, ttk
import csv
import time
import re
import math
from collections import Counter
import mmh3
from bitarray import bitarray

# ================= CONFIGURATION =================
PATH_CSV = r"C:\VSCode\Cpp_project\DSA\project\data\enron_spam_data.csv"
csv.field_size_limit(10 * 1024 * 1024)  # 10MB per field

# Modern Color Palette
BG_MAIN = "#0f172a"      # Dark slate
BG_PANEL = "#1e293b"     # Darker slate
BG_INPUT = "#334155"     # Slate gray
ACCENT = "#3b82f6"       # Blue
ACCENT_HOVER = "#2563eb" # Darker blue
SUCCESS = "#10b981"      # Green
ERROR = "#ef4444"        # Red
TEXT_PRIMARY = "#f1f5f9" # Light gray
TEXT_SECONDARY = "#94a3b8" # Gray
BORDER = "#475569"       # Border gray

# ================= BLOOM FILTER =================
class BloomFilter:
    """Bloom Filter with MurmurHash3"""
    def __init__(self, n, p=0.01):
        """
        n: expected number of items
        p: false positive probability
        """
        self.m = int(-(n * math.log(p)) / (math.log(2) ** 2))
        self.k = int((self.m / n) * math.log(2))
        self.bits = bitarray(self.m)
        self.bits.setall(0)
        self.item_count = 0

    def add(self, item):
        """Add an item to the filter"""
        for i in range(self.k):
            idx = mmh3.hash(item, i) % self.m
            self.bits[idx] = 1
        self.item_count += 1

    def contains(self, item):
        """Check if item might be in the set"""
        for i in range(self.k):
            idx = mmh3.hash(item, i) % self.m
            if not self.bits[idx]:
                return False
        return True
    
    def get_stats(self):
        """Get filter statistics"""
        filled = self.bits.count()
        return {
            "size": self.m,
            "hash_functions": self.k,
            "items": self.item_count,
            "filled_bits": filled,
            "load_factor": filled / self.m
        }

# ================= NAIVE BAYES =================
class NaiveBayes:
    """Multinomial Naive Bayes classifier with Laplace smoothing"""
    def __init__(self):
        self.spam_counts = Counter()
        self.ham_counts = Counter()
        self.spam_total = 0
        self.ham_total = 0
        self.spam_docs = 0
        self.ham_docs = 0
        self.vocab = set()

    def tokenize(self, text):
        """Extract words (2+ letters)"""
        return re.findall(r"\b[a-z]{2,}\b", text.lower())

    def train(self, text, label):
        """Train on a single document"""
        tokens = self.tokenize(text)
        
        if label == "spam":
            self.spam_counts.update(tokens)
            self.spam_total += len(tokens)
            self.spam_docs += 1
        else:
            self.ham_counts.update(tokens)
            self.ham_total += len(tokens)
            self.ham_docs += 1
        
        self.vocab.update(tokens)

    def predict(self, text):
        """Predict class for given text"""
        # Check if model is trained
        if self.spam_total == 0 and self.ham_total == 0:
            return "ham"  # Default to ham if not trained
        
        tokens = self.tokenize(text)
        vocab_size = max(len(self.vocab), 1)  # Avoid division by zero
        
        # Prior probabilities
        total_docs = self.spam_docs + self.ham_docs
        p_spam = self.spam_docs / total_docs if total_docs > 0 else 0.5
        p_ham = self.ham_docs / total_docs if total_docs > 0 else 0.5
        
        log_spam = math.log(p_spam)
        log_ham = math.log(p_ham)

        # Likelihood with Laplace smoothing
        for token in tokens:
            spam_denom = self.spam_total + vocab_size
            ham_denom = self.ham_total + vocab_size
            
            p_token_spam = (self.spam_counts[token] + 1) / spam_denom if spam_denom > 0 else 0.5
            p_token_ham = (self.ham_counts[token] + 1) / ham_denom if ham_denom > 0 else 0.5
            
            log_spam += math.log(p_token_spam)
            log_ham += math.log(p_token_ham)

        return "spam" if log_spam > log_ham else "ham"
    
    def predict_proba(self, text):
        """Return probability scores"""
        # Check if model is trained
        if self.spam_total == 0 and self.ham_total == 0:
            return {"spam": 0.5, "ham": 0.5}
        
        tokens = self.tokenize(text)
        vocab_size = max(len(self.vocab), 1)
        
        total_docs = self.spam_docs + self.ham_docs
        p_spam = self.spam_docs / total_docs if total_docs > 0 else 0.5
        p_ham = self.ham_docs / total_docs if total_docs > 0 else 0.5
        
        log_spam = math.log(p_spam)
        log_ham = math.log(p_ham)

        for token in tokens:
            spam_denom = self.spam_total + vocab_size
            ham_denom = self.ham_total + vocab_size
            
            p_token_spam = (self.spam_counts[token] + 1) / spam_denom if spam_denom > 0 else 0.5
            p_token_ham = (self.ham_counts[token] + 1) / ham_denom if ham_denom > 0 else 0.5
            
            log_spam += math.log(p_token_spam)
            log_ham += math.log(p_token_ham)
        
        # Convert log probabilities to probabilities
        max_log = max(log_spam, log_ham)
        exp_spam = math.exp(log_spam - max_log)
        exp_ham = math.exp(log_ham - max_log)
        total = exp_spam + exp_ham
        
        return {
            "spam": exp_spam / total,
            "ham": exp_ham / total
        }

# ================= SPAM INDICATORS =================
SPAM_KEYWORDS = [
    "win money", "won money", "cash prize", "claim your prize",
    "lottery winner", "you are the winner", "jackpot",
    "million dollars", "instant cash", "easy money",
    "earn money fast", "get rich quick",
    "limited time offer", "special promotion", "act now",
    "order now", "buy now", "free trial", "free offer",
    "100% free", "no cost", "huge discount", "cheap price",
    "click here", "click the link", "visit our website",
    "verify your account", "confirm your account",
    "login immediately", "security alert",
    "unusual activity", "update your information",
    "account suspended", "account will be closed",
    "no prescription needed", "fast delivery worldwide",
    "dear friend", "dear customer", "dear user",
    "valued customer",
    "urgent message", "reply immediately", "urgent",
    "attention required", "immediate action required",
    "online casino", "online betting", "poker", "casino",
    "viagra", "cialis", "weight loss",
    "lose weight fast", "miracle cure",
    "congratulations", "this is not spam"
]

SPAM_SENDERS = [
    "promo@", "lottery@", "reward@", "noreply@",
    "winner@", "support@security", "info@promo"
]

SUSPICIOUS_DOMAINS = [
    ".ru", ".xyz", ".top", ".click", ".pw",
    "freegift.com", "claim-now.com",
    "secure-login.net", "verify-account.org"
]

# ================= GLOBAL INSTANCES =================
nb = NaiveBayes()
INDICATORS = SPAM_KEYWORDS + SPAM_SENDERS + SUSPICIOUS_DOMAINS
bf = BloomFilter(len(INDICATORS), p=0.01)

for indicator in INDICATORS:
    bf.add(indicator)

# ================= TRAINING =================
def train_nb_from_csv(path, limit=None):
    """Train Naive Bayes from CSV file"""
    try:
        with open(path, newline='', encoding="utf-8", errors="ignore") as f:
            reader = csv.DictReader(f)
            count = 0
            for i, row in enumerate(reader):
                if limit and i >= limit:
                    break
                
                # Handle missing columns gracefully
                subject = row.get('Subject', '')
                message = row.get('Message', '')
                spam_ham = row.get('Spam/Ham', '').lower().strip()
                
                if not spam_ham:
                    continue
                
                text = f"{subject} {message}"
                nb.train(text, spam_ham)
                count += 1
            
            print(f"✓ Training completed: {count} emails")
            print(f"  - Spam docs: {nb.spam_docs}")
            print(f"  - Ham docs: {nb.ham_docs}")
            print(f"  - Vocabulary size: {len(nb.vocab)}")
            return count
    except FileNotFoundError:
        print(f"⚠ Warning: Training file not found: {path}")
        print(f"  Model will work with Bloom Filter only until trained.")
        return 0
    except Exception as e:
        print(f"✗ Error training model: {e}")
        import traceback
        traceback.print_exc()
        return 0

# Train model on startup
print("="*60)
print("INITIALIZING SPAM DETECTOR")
print("="*60)
trained_count = train_nb_from_csv(PATH_CSV)
if trained_count == 0:
    print("⚠ Warning: No training data loaded. Use 'Bloom Filter Only' mode.")
print("="*60)

# ================= FEATURE EXTRACTION =================
def bloom_score(text):
    """Calculate spam score using Bloom Filter"""
    score = 0
    text_lower = text.lower()

    # Check sender email
    sender_match = re.search(r'From:\s*<?([^\s<>]+@[^\s<>]+)>?', text, re.I)
    if sender_match:
        email = sender_match.group(1).lower()
        if bf.contains(email):
            score += 4
        
        domain = email.split("@")[-1] if "@" in email else email
        if bf.contains(domain):
            score += 3

    # Check subject line
    subject_match = re.search(r'Subject:\s*(.*?)(?:\n|$)', text, re.I)
    if subject_match:
        subject = subject_match.group(1).lower()
        for keyword in SPAM_KEYWORDS:
            if keyword in subject and bf.contains(keyword):
                score += 2
                break  # Count once per subject

    # Check body for spam keywords
    for keyword in SPAM_KEYWORDS:
        if keyword in text_lower and bf.contains(keyword):
            score += 1

    # Check for suspicious domains
    for domain in SUSPICIOUS_DOMAINS:
        if domain in text_lower and bf.contains(domain):
            score += 2

    # Reduce score for internal emails
    if is_internal_enron_mail(text):
        score = max(0, score - 5)

    return score

def is_internal_enron_mail(text):
    """Detect if email is internal Enron communication"""
    patterns = [
        r"forwarded by",
        r"/hou/ect",
        r"enron\.com",
        r"@enron",
        r"From\s*:\s*\S+@enron",
        r"To\s*:\s*\S+@enron"
    ]
    hits = sum(bool(re.search(p, text, re.I)) for p in patterns)
    return hits >= 2

# ================= EVALUATION =================
def evaluate_csv(path, threshold, mode="bloom"):
    """Evaluate model on CSV dataset"""
    start = time.time()
    total = correct = fp = fn = ham_count = spam_count = 0

    try:
        with open(path, newline='', encoding="utf-8", errors="ignore") as f:
            reader = csv.DictReader(f)
            
            # Check if required columns exist
            first_row = next(reader, None)
            if first_row is None:
                raise ValueError("CSV file is empty")
            
            # Check columns
            if 'Subject' not in first_row or 'Message' not in first_row or 'Spam/Ham' not in first_row:
                raise ValueError(f"CSV must have 'Subject', 'Message', and 'Spam/Ham' columns.\nFound: {list(first_row.keys())}")
            
            # Reset file pointer
            f.seek(0)
            reader = csv.DictReader(f)
            
            for row in reader:
                subject = row.get('Subject', '')
                message = row.get('Message', '')
                spam_ham = row.get('Spam/Ham', '').lower().strip()
                
                if not spam_ham:
                    continue
                
                text = f"{subject} {message}"
                true_spam = (spam_ham == "spam")

                score = bloom_score(text)

                if mode == "bloom":
                    pred_spam = (score >= threshold)
                else:  # hybrid mode
                    if score < threshold:
                        pred_spam = False
                    else:
                        pred_spam = (nb.predict(text) == "spam")

                total += 1
                if pred_spam == true_spam:
                    correct += 1
                
                if true_spam:
                    spam_count += 1
                    if not pred_spam:
                        fn += 1
                else:
                    ham_count += 1
                    if pred_spam:
                        fp += 1

        if total == 0:
            raise ValueError("No valid emails found in CSV")

        accuracy = correct / total
        fpr = fp / ham_count if ham_count > 0 else 0
        fnr = fn / spam_count if spam_count > 0 else 0
        
        tp = spam_count - fn
        precision = tp / (tp + fp) if (tp + fp) > 0 else 0
        recall = tp / spam_count if spam_count > 0 else 0
        f1 = 2 * (precision * recall) / (precision + recall) if (precision + recall) > 0 else 0
        
        elapsed = time.time() - start
        
        return {
            "total": total,
            "correct": correct,
            "accuracy": accuracy,
            "fpr": fpr,
            "fnr": fnr,
            "precision": precision,
            "recall": recall,
            "f1": f1,
            "time": elapsed,
            "ham": ham_count,
            "spam": spam_count,
            "fp": fp,
            "fn": fn
        }
    except Exception as e:
        print(f"Error evaluating CSV: {e}")
        import traceback
        traceback.print_exc()
        return None

# ================= GUI COMPONENTS =================
class SpamDetectorGUI:
    def __init__(self, root):
        self.root = root
        self.setup_window()
        self.create_widgets()
        
    def setup_window(self):
        """Configure main window"""
        self.root.title("🛡️ Spam Detector - Bloom Filter + Naive Bayes")
        self.root.geometry("1200x700")
        self.root.configure(bg=BG_MAIN)
        self.root.minsize(900, 600)
        
    def create_widgets(self):
        """Create all GUI widgets"""
        # Main container
        main_container = tk.Frame(self.root, bg=BG_MAIN)
        main_container.pack(fill=tk.BOTH, expand=True, padx=16, pady=16)
        
        # Left panel
        self.create_left_panel(main_container)
        
        # Right panel
        self.create_right_panel(main_container)
        
    def create_left_panel(self, parent):
        """Create left control panel"""
        left_panel = tk.Frame(parent, bg=BG_PANEL, width=320)
        left_panel.pack(side=tk.LEFT, fill=tk.Y, padx=(0, 12))
        left_panel.pack_propagate(False)
        
        # Title
        tk.Label(
            left_panel,
            text="⚙️ Control Panel",
            font=("Segoe UI", 16, "bold"),
            bg=BG_PANEL,
            fg=TEXT_PRIMARY
        ).pack(pady=(16, 20))
        
        # File operations section
        self.create_section_label(left_panel, "📁 File Operations")
        
        self.create_button(
            left_panel,
            "📂 Load Email (.txt)",
            self.open_file,
            pady=8
        )
        
        self.create_button(
            left_panel,
            "📊 Evaluate Dataset",
            self.evaluate_dataset,
            pady=8
        )
        
        # Threshold section
        self.create_section_label(left_panel, "🎯 Detection Threshold", pady_top=20)
        
        threshold_frame = tk.Frame(left_panel, bg=BG_PANEL)
        threshold_frame.pack(fill=tk.X, padx=16, pady=8)
        
        self.threshold_var = tk.IntVar(value=3)
        self.threshold_label = tk.Label(
            threshold_frame,
            text="Threshold: 3",
            font=("Segoe UI", 10),
            bg=BG_PANEL,
            fg=TEXT_SECONDARY
        )
        self.threshold_label.pack()
        
        self.threshold_scale = tk.Scale(
            threshold_frame,
            from_=1,
            to=10,
            orient=tk.HORIZONTAL,
            variable=self.threshold_var,
            command=self.update_threshold_label,
            bg=BG_PANEL,
            fg=TEXT_PRIMARY,
            troughcolor=BG_INPUT,
            highlightthickness=0,
            sliderrelief=tk.FLAT,
            activebackground=ACCENT
        )
        self.threshold_scale.pack(fill=tk.X, pady=4)
        
        # Mode selection
        self.create_section_label(left_panel, "🔧 Detection Mode", pady_top=16)
        
        self.mode_var = tk.StringVar(value="hybrid")
        
        mode_frame = tk.Frame(left_panel, bg=BG_PANEL)
        mode_frame.pack(fill=tk.X, padx=16, pady=8)
        
        tk.Radiobutton(
            mode_frame,
            text="Bloom Filter Only",
            variable=self.mode_var,
            value="bloom",
            bg=BG_PANEL,
            fg=TEXT_PRIMARY,
            selectcolor=BG_INPUT,
            activebackground=BG_PANEL,
            font=("Segoe UI", 10)
        ).pack(anchor="w", pady=2)
        
        tk.Radiobutton(
            mode_frame,
            text="Bloom + Naive Bayes (Hybrid)",
            variable=self.mode_var,
            value="hybrid",
            bg=BG_PANEL,
            fg=TEXT_PRIMARY,
            selectcolor=BG_INPUT,
            activebackground=BG_PANEL,
            font=("Segoe UI", 10)
        ).pack(anchor="w", pady=2)
        
        # Check button
        self.create_button(
            left_panel,
            "🚀 Detect Spam",
            self.check_email,
            pady=20,
            bg=SUCCESS
        )
        
        # Statistics section
        self.create_section_label(left_panel, "📈 Statistics", pady_top=16)
        
        self.stats_label = tk.Label(
            left_panel,
            text="No evaluation yet",
            font=("Consolas", 9),
            bg=BG_PANEL,
            fg=TEXT_SECONDARY,
            justify=tk.LEFT,
            anchor="w"
        )
        self.stats_label.pack(fill=tk.X, padx=16, pady=8)
        
    def create_right_panel(self, parent):
        """Create right content panel"""
        right_panel = tk.Frame(parent, bg=BG_PANEL)
        right_panel.pack(side=tk.RIGHT, fill=tk.BOTH, expand=True)
        
        # Header
        header_frame = tk.Frame(right_panel, bg=BG_PANEL)
        header_frame.pack(fill=tk.X, padx=16, pady=(16, 8))
        
        tk.Label(
            header_frame,
            text="📧 Email Content",
            font=("Segoe UI", 16, "bold"),
            bg=BG_PANEL,
            fg=TEXT_PRIMARY
        ).pack(side=tk.LEFT)
        
        # Text editor
        text_frame = tk.Frame(right_panel, bg=BG_INPUT)
        text_frame.pack(fill=tk.BOTH, expand=True, padx=16, pady=8)
        
        self.email_text = tk.Text(
            text_frame,
            wrap=tk.WORD,
            font=("Consolas", 10),
            bg=BG_INPUT,
            fg=TEXT_PRIMARY,
            insertbackground=TEXT_PRIMARY,
            relief=tk.FLAT,
            padx=12,
            pady=12
        )
        self.email_text.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        
        scrollbar = tk.Scrollbar(text_frame, command=self.email_text.yview)
        scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
        self.email_text.config(yscrollcommand=scrollbar.set)
        
        # Result section
        result_frame = tk.Frame(right_panel, bg=BG_PANEL)
        result_frame.pack(fill=tk.X, padx=16, pady=(8, 16))
        
        self.result_label = tk.Label(
            result_frame,
            text="Result: ---",
            font=("Segoe UI", 18, "bold"),
            bg=BG_PANEL,
            fg=TEXT_PRIMARY
        )
        self.result_label.pack(pady=8)
        
        self.detail_label = tk.Label(
            result_frame,
            text="",
            font=("Segoe UI", 10),
            bg=BG_PANEL,
            fg=TEXT_SECONDARY
        )
        self.detail_label.pack()
        
    def create_section_label(self, parent, text, pady_top=16):
        """Create section header label"""
        tk.Label(
            parent,
            text=text,
            font=("Segoe UI", 11, "bold"),
            bg=BG_PANEL,
            fg=TEXT_SECONDARY
        ).pack(pady=(pady_top, 4))
        
    def create_button(self, parent, text, command, pady=4, bg=ACCENT):
        """Create styled button"""
        btn = tk.Button(
            parent,
            text=text,
            command=command,
            bg=bg,
            fg="white",
            font=("Segoe UI", 10, "bold"),
            relief=tk.FLAT,
            padx=16,
            pady=10,
            cursor="hand2",
            activebackground=ACCENT_HOVER,
            activeforeground="white"
        )
        btn.pack(fill=tk.X, padx=16, pady=pady)
        
        # Hover effects
        hover_color = ACCENT_HOVER if bg == ACCENT else "#0d9488"
        btn.bind("<Enter>", lambda e: btn.config(bg=hover_color))
        btn.bind("<Leave>", lambda e: btn.config(bg=bg))
        
        return btn
    
    def update_threshold_label(self, value):
        """Update threshold label"""
        self.threshold_label.config(text=f"Threshold: {value}")
    
    def open_file(self):
        """Open and load email file"""
        path = filedialog.askopenfilename(
            title="Select Email File",
            filetypes=[("Text files", "*.txt"), ("All files", "*.*")]
        )
        if not path:
            return
        
        try:
            with open(path, "r", encoding="utf-8", errors="ignore") as f:
                content = f.read()
                self.email_text.delete("1.0", tk.END)
                self.email_text.insert(tk.END, content)
            self.result_label.config(text="Result: ---", fg=TEXT_PRIMARY)
            self.detail_label.config(text="")
        except Exception as e:
            messagebox.showerror("Error", f"Could not load file:\n{e}")
    
    def check_email(self):
        """Detect spam in current email"""
        email_content = self.email_text.get("1.0", tk.END).strip()
        
        if not email_content:
            messagebox.showwarning("Warning", "Please load an email first!")
            return
        
        threshold = self.threshold_var.get()
        mode = self.mode_var.get()
        
        # Calculate bloom score
        score = bloom_score(email_content)
        
        # Check if NB is trained for hybrid mode
        if mode == "hybrid" and nb.spam_total == 0 and nb.ham_total == 0:
            messagebox.showwarning(
                "Model Not Trained",
                "Naive Bayes model is not trained yet.\n"
                "Please load a training CSV or use 'Bloom Filter Only' mode."
            )
            return
        
        # Determine result based on mode
        if mode == "bloom":
            is_spam = (score >= threshold)
            method = "Bloom Filter"
            detail = f"Bloom Score: {score} | Threshold: {threshold}"
        else:  # hybrid
            if score < threshold:
                is_spam = False
                method = "Bloom Filter (early accept)"
                detail = f"Bloom Score: {score} < {threshold} (threshold)"
            else:
                nb_result = nb.predict(email_content)
                proba = nb.predict_proba(email_content)
                is_spam = (nb_result == "spam")
                method = f"Naive Bayes"
                detail = f"Bloom: {score} | NB Confidence: Spam={proba['spam']:.1%}, Ham={proba['ham']:.1%}"
        
        # Update UI
        result_text = "SPAM ⚠️" if is_spam else "HAM ✅"
        result_color = ERROR if is_spam else SUCCESS
        
        self.result_label.config(text=f"Result: {result_text}", fg=result_color)
        self.detail_label.config(text=f"{detail} | Method: {method}")
    
    def evaluate_dataset(self):
        """Evaluate on CSV dataset"""
        path = filedialog.askopenfilename(
            title="Select Dataset CSV",
            filetypes=[("CSV files", "*.csv"), ("All files", "*.*")]
        )
        if not path:
            return
        
        threshold = self.threshold_var.get()
        mode = self.mode_var.get()
        
        # Check if NB is trained for hybrid mode
        if mode == "hybrid" and nb.spam_total == 0 and nb.ham_total == 0:
            result = messagebox.askyesno(
                "Model Not Trained",
                "Naive Bayes model is not trained.\n\n"
                "Do you want to train it on this CSV first?\n"
                "(This will take a moment)"
            )
            if result:
                self.stats_label.config(text="Training model... Please wait...")
                self.root.update()
                count = train_nb_from_csv(path)
                if count == 0:
                    messagebox.showerror("Error", "Failed to train model from CSV")
                    self.stats_label.config(text="Training failed")
                    return
                else:
                    messagebox.showinfo("Success", f"Model trained on {count} emails!")
        
        # Show progress
        self.stats_label.config(text="Evaluating... Please wait...")
        self.root.update()
        
        # Evaluate
        results = evaluate_csv(path, threshold, mode)
        
        if results is None:
            messagebox.showerror("Error", "Failed to evaluate dataset.\nCheck console for details.")
            self.stats_label.config(text="Evaluation failed")
            return
        
        # Display results
        stats_text = (
            f"Dataset Evaluation Results\n"
            f"{'─' * 30}\n"
            f"Total emails: {results['total']}\n"
            f"  • HAM: {results['ham']}\n"
            f"  • SPAM: {results['spam']}\n"
            f"{'─' * 30}\n"
            f"Accuracy: {results['accuracy']:.2%}\n"
            f"Precision: {results['precision']:.2%}\n"
            f"Recall: {results['recall']:.2%}\n"
            f"F1-Score: {results['f1']:.2%}\n"
            f"{'─' * 30}\n"
            f"False Positive: {results['fp']}/{results['ham']}\n"
            f"FP Rate: {results['fpr']:.2%}\n"
            f"False Negative: {results['fn']}/{results['spam']}\n"
            f"FN Rate: {results['fnr']:.2%}\n"
            f"{'─' * 30}\n"
            f"Time: {results['time']:.2f}s\n"
            f"Mode: {mode.upper()}"
        )
        
        self.stats_label.config(text=stats_text)
        messagebox.showinfo("Evaluation Complete", f"Accuracy: {results['accuracy']:.2%}")

# ================= MAIN =================
if __name__ == "__main__":
    root = tk.Tk()
    app = SpamDetectorGUI(root)
    root.mainloop()