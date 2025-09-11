#include<bits/stdc++.h>

using namespace std;

void print_arr(int *a, int n) {
    for (int i = 0; i < n; i++) {
        cout << a[i];
    }
    cout << endl;
}

void fill_arr(int begin, int end, int *a, int k) {
    for (int i = begin; i < end; i++) {
        a[i] = k;
    }
}

void binary_string(int *a, int n) {

    while (true) {
        print_arr(a, n);
        int i = (n) - 1;
        while ((i >= 0) and (a[i] == 1)) {
            i--;
        }
        if (i < 0) break;
        a[i] = 1;
        fill_arr(i + 1, n, a, 0);
    }

}

void Try(int i, int *a, int n) {
    for (int j = 0; j <= 1; j++) {
        a[i] = j;
        if (i == (n - 1)) {
            print_arr(a, n);
        } else {
            Try(i + 1, a, n);
        }
    }
}

int main() {
    int n;
    cin >> n;
    int *a = new int[n]();
    
    // binary_string(a, n);
    Try(0, a, n);

    delete[] a;
    return 0;
}