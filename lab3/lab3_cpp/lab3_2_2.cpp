#include <bits/stdc++.h>

using namespace std;

int ans[2];

void sum_of_2(int *a, int S, int l, int r) {
    if (l >= r) return;

    int m = (l + r)/2;
    sum_of_2(a, S, l, m);
    sum_of_2(a, S, m + 1, r);

    int i = l;
    int j = r;
    while (i <= m and j > m) {
        int sum = a[i] + a[j];
        if (sum == S) {
            ans[0] = a[i];
            ans[1] = a[j];
            return;
        }
        else if (sum > S)
            j--;
        else 
            i++;
    }
}

int main() {
    int S;
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    sum_of_2(a, 13, 0, 9);
    cout << ans[0] << " " << ans[1];
}