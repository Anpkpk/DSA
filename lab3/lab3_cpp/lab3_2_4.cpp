#include <bits/stdc++.h>

using namespace std;

int cmp = 0;

int second_max(int *a, int n) {
    int max = a[0];
    int sec_max = INT_MIN;

    for (int i = 1; i < n; i++) {
        if (a[i] > max) {
            sec_max = max;
            max = a[i];
            cmp++;
        }
        else {
            if (a[i] > sec_max) {
                sec_max = a[i];
                cmp++;
            }
        }
    }
    return sec_max;
}

int main() {
    int a[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    cout << second_max(a, 9) << endl;
    cout << cmp << endl;
}