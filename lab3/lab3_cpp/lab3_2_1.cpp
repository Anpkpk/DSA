#include<bits/stdc++.h>

using namespace std;

int count_rec(int *a, int x, int l, int r) {
    if (l > r) return 0;
    if (l == r) return (a[l] == x);

    int m = (l + r) / 2;
    return count_rec(a, x, l, m) + count_rec(a, x, m + 1, r);
}

int main() {
    int a[6] = {1, 4, 3, 2, 5, 2};
    cout << count_rec(a, 5, 0, 5) << endl;
}