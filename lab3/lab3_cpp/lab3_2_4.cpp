#include <bits/stdc++.h>

using namespace std;

int second_max(int *a, int n) {
    int max = a[0];
    int sec_max = INT_MIN;

    for (int i = 1; i < n; i++) {
        if (a[i] > max) {
            sec_max = max;
            max = a[i];
        }
        else {
            if (a[i] > sec_max) {
                sec_max = a[i];
            }
        }
    }
    return sec_max;
}

int main() {
    int a[5] = {1, 2, 4, 3, 0};
    cout << second_max(a, 5) << endl;
}