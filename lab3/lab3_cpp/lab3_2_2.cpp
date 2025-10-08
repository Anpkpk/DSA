#include<bits/stdc++.h>

using namespace std;

pair<int, int> find_pair(int *a, int s, int l, int r) {
    if (l >= r) return {-1, -1};
    int m = (l + r) / 2;
    
    auto result = find_pair(a, s, l, m);
    if (result.first != -1) {
        return result;
    }

    result = find_pair(a, s, m + 1, r);
    if (result.first != -1) {
        return result;
    }

    int i = m;
    int j = m + 1;
    while (i >= l and j <= r) {
        int sum = a[i] + a[j];
        if (sum == s) {
            return {i, j};
        }
        else if (sum > s) {
            i -= 1;
        }
        else {
            j += 1;
        }
    }
    return {-1, -1};
}

int main() {
    int a[6] = {1, 4, 3, 2, 5, 2};

    auto res = find_pair(a, 8, 0, 5);
    cout << res.first << " " << res.second << endl;
}