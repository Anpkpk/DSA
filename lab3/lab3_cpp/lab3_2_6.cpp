#include <bits/stdc++.h>

using namespace std;

int max_crossing_sum(int *a, int l, int m, int r) {
    int sum = 0;
    int left_sum = INT_MIN;
    for (int i = m; i >= l; i--) {
        sum = sum + a[i];
        if (sum > left_sum)
            left_sum = sum;
    }

    sum = 0;
    int right_sum = INT_MIN;
    for (int i = m + 1; i <= r; i++) {
        sum = sum + a[i];
        if (sum > right_sum)
            right_sum = sum;
    }

    return (left_sum + right_sum);
}


int max_sum(int *a, int l, int r) {
    if (l > r)
        return INT_MIN;

    if (l == r)
        return a[l];

    int m = l + (r - l) / 2;

    int left_sum = max_sum(a, l, m);
    int right_sum = max_sum(a, m + 1, r);
    int cross_sum = max_crossing_sum(a, l, m, r);

    if (left_sum >= right_sum && left_sum >= cross_sum)
        return left_sum;
    else if (right_sum >= left_sum && right_sum >= cross_sum)
        return right_sum;
    else
        return cross_sum;
}

int main() {
    int a[5] = {2, -3, 4, -5, 7};

    cout << max_sum(a, 0, 4);
    return 0;
}