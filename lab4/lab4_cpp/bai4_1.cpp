#include <bits/stdc++.h>

using namespace std;

bool cmp(string a, string b) {
    int n = min(a.length(), b.length());
    for (int i = 0; i < n; i++) {
        a[i] = toupper(a[i]);
        b[i] = toupper(b[i]);
        if (a[i] > b[i]) {
            return 0;
        }
        else return 1;
    } 
}

int main() {
    vector<string> s = {"Banana", "date", "cherry", "apple"};
    sort(s.begin(), s.end(), cmp);

    for (auto x : s) {
        cout << x << " "; 
    }
}