#include<iostream>

using namespace std;

int max_3(int a, int b, int c) {
    if (a > b && a > c) {
        return a;
    }
    else if (b > c) {
        return b;
    }
    else {
        return c;
    }
}

int main() {
    int a, b, c;
    cin >> a >> b >> c;

    cout << max_3(a, b, c);
}