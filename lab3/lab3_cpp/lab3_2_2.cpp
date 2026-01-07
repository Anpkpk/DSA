#include <bits/stdc++.h>

using namespace std;

int ans[2];

bool sum_of_2(int *a, int S, int l, int r) {
    if (l >= r) return false;

    int m = (l + r)/2;
    if (sum_of_2(a, S, l, m)) return true;
    if (sum_of_2(a, S, m + 1, r)) return true;

    int i = l;
    int j = r;
    while (i <= m and j > m) {
        int sum = a[i] + a[j];
        if (sum == S) {
            ans[0] = a[i];
            ans[1] = a[j];
            return true;
        }
        else if (sum > S)
            j--;
        else 
            i++;
    }
    return false;
}

int main() {
    int S;
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    sum_of_2(a, 13, 0, 9);
    cout << ans[0] << " " << ans[1];
}