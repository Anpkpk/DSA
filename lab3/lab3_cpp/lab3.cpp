#include<bits/stdc++.h>

using namespace std;

int cnt_search(int *a, int x, int l, int r) {
    if (l >= r) {
        if (a[l] == x) return 1;
        else return 0;
    }
    int m = (l + r) / 2;
    if (a[m] == x) return 1;
    return cnt_search(a, x, l, m) + cnt_search(a, x, m + 1, r);
}

int main() {
    int a[6] = {1, 4, 3, 2, 5, 2};
    cout << cnt_search(a, 2, 0, 5);
}