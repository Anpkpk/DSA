#include <bits/stdc++.h>

using namespace std;

void std_string(string &s) {
    if (s.empty()) return;

    while (!s.empty() && s[0] == ' ') {
        s.erase(0, 1);
    }

    while (!s.empty() && s.back() == ' ') {
        s.pop_back();
    }

    for (int i = 1; i < s.length(); i++) {
        while (s[i] == ' ' and s[i - 1] == ' ') {
            s.erase(i - 1, 1);
        }
    }
}


int count_word(string &s) {
    std_string(s);
    int cnt = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ' ') {
            ++cnt;
        }
    }
    return cnt+1;
}

int is_palindrome(string &s) {
    if (s.length() == 1) return 1;
    int l = 0;
    int r = s.length() - 1;

    while (l <= r) {
        if (s[l] != s[r]) {
            return 0;
        }
        ++l;
        --r;
    }
    return 1;
}

string replace_exact_word(const string &s, const string &old_word, const string &new_word) {
    stringstream ss(s);
    string word, res;
    while (ss >> word) {
        if (word == old_word) {
            res += new_word;
        }
        else {
            res += word;
        }    
        res += " ";
    }
    if (!res.empty()) res.pop_back();
    return res;
}

int find_word(string &s, string word) {
    int i = 0;
    stringstream ss(s);
    string w, res;
    while (ss >> w) {
        if (w == word) {
            return i;
        }
        ++i;    
    }
    return i;
}

string replace_exact_char(string &s, const char old_char, const char new_char) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == old_char) {
            s[i] = new_char;
        }
    } 
}

int main() {
    string s;
    getline(cin, s);
    
    // cout << count_word(s) << endl;

    // reverse(s.begin(), s.end());
    // cout << s << endl;

    // cout << is_palindrome(s) << endl;

    // string new_s = replace_exact_word(s, "a", "b");
    // cout << new_s;

    cout << find_word(s, "an");
}