#include<iostream>

using namespace std;

void fibonacci(int n) {
    int f0 = 0;
    int f1 = 1;
    int f2 = f0 + f1;

    if (n <= 0) {
        cout << 0;
    }

    for (int i = 1; i <= n; i++) {
        cout << f2 << " ";
        f0 = f1;
        f1 = f2;
        f2 = f0 + f1;
    }
}

int main() {
    int n;
    cin >> n;

    fibonacci(n);
}