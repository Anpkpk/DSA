#include <bits/stdc++.h>

using namespace std;

void prime(int a, int b) {
    int is_prime[b] = {0};
    is_prime[0] = is_prime[1] = 1;

    for (int i = 2; i * i <= b; i++) {
        if (!is_prime[i]) {
            for (int j = i * i; j <= b; j += i) {
                is_prime[j] = 1;
            }
        }
    }

    cout << "Cac so nguyen to trong [" << a << ", " << b << "]: ";
    for (int i = a; i <= b; i++) {
        if (!is_prime[i]) cout << i << " ";
    }
    cout << endl;
}

int main() {
    int a, b;
    cin >> a >> b;
    prime(a, b);
}