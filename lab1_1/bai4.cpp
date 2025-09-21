#include <bits/stdc++.h>

using namespace std;

long factorial(int n) {
    if (n <= 0) return 0;
    long fact = 1;
    for (int i = 2; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

void fibonaci(int *fibo, int n) {
     if (n < 1) {
        cout << 0 << endl;
        return;
    }

    fibo[0] = 0;
    fibo[1] = 1;

    cout << fibo[0] << " " << fibo[1] << " ";

    for (int i = 2; i <= n; i++) {
        fibo[i] = fibo[i - 1] + fibo[i - 2];
        cout << fibo[i] << " ";
    }
    cout << endl;
}

string string_concate(int *fibo, int n) {
    if (n <= 0) return "";
    string ans = "";

    for (int i = 0; i <= n; i++) {
        ans += to_string(fibo[i]);
    }
    
    return ans;
}

void reverse_string(string &s) {
    int l = 0, r = s.size() - 1;
    while (l < r) {
        swap(s[l], s[r]);
        l++, r--;
    }
}

int main() {
    int n;
    cin >> n;

    cout << factorial(n) << endl;

    int *fibo = new int[n];
    fibonaci(fibo, n);
    
    string ans = string_concate(fibo, n);
    cout << ans << endl;
    reverse_string(ans);
    cout << ans << endl;

    delete[] fibo;
}