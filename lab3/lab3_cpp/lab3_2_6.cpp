#include <bits/stdc++.h>

using namespace std;

vector<int> burte_force(vector<int> a, int n) {
    int min, max;
    int max_value = 0;
    for (int i = 0; i < n-1; i++) {
        for (int j = i + 1; j < n; j++) {
            int value = a[j] - a[i];
            if (value > max_value) {
                min = i;
                max = j;
                max_value = value;
            }
        }
    }
    vector<int> ans;
    ans.push_back(min);
    ans.push_back(max);
    ans.push_back(max_value);
    
    return ans;
}

vector<int> divide_conquer(vector<int> &A, int low, int high) {
    if (low == high) {
        return {low, high, 0}; 
    }

    int mid = (low + high) / 2;

    vector<int> left = divide_conquer(A, low, mid);
    vector<int> right = divide_conquer(A, mid + 1, high);

    int min_left_idx = low;
    for (int i = low + 1; i <= mid; i++) {
        if (A[i] < A[min_left_idx]) min_left_idx = i;
    }

    int max_right_idx = mid + 1;
    for (int j = mid + 2; j <= high; j++) {
        if (A[j] > A[max_right_idx]) max_right_idx = j;
    }

    int cross_value = A[max_right_idx] - A[min_left_idx];
    vector<int> cross = {min_left_idx, max_right_idx, cross_value};

    if (left[2] >= right[2] && left[2] >= cross[2])
        return left;
    else if (right[2] >= left[2] && right[2] >= cross[2])
        return right;
    else
        return cross;
}

int main() {
    vector<int> a = {100, 113, 110, 85, 105,
                     102, 86, 63, 75, 95, 88,
                     92, 78, 105, 98};

    // vector<int> ans = burte_force(a, a.size());
    // cout << "Buy: " << ans[0] + 1 << endl;
    // cout << "Sell: " << ans[1] + 1 << endl;
    // cout << "Max: " << ans[2] << endl;

    vector<int> ans = divide_conquer(a, 0, a.size() - 1);
    cout << "Buy: " << ans[0] + 1 << endl;
    cout << "Sell: " << ans[1] + 1 << endl;
    cout << "Max: " << ans[2] << endl;

    return 0;
}