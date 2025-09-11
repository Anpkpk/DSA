#include <bits/stdc++.h>

using namespace std;

int *create_arr(int n) {
    int *a = new int[n];
    return a;
}

void scan_arr(int *a, int n) {
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
}

void print_arr(int *a, int n) {
    for (int i = 0; i < n; i++) {
        if (i == n - 1) {
            cout << a[i];    
        } else {
            cout << a[i] << " ";
        }
    }
    cout << endl;
} 

vector<int> min_max_element(int *a, int n) {
    int max = a[0];
    int min = a[0];
    for (int i = 0; i < n; i++) {
        if (a[i] > a[0]) {
            max = a[i];
        }
        if (a[i] < min) {
            min = a[i];
        }
    }
    return {max, min};
}

void print_min_max(int *a, int n) {
    vector<int> max_min = min_max_element(a, n);
    cout << "max: " << *max_min.begin() << endl;
    cout << "min: " << *(max_min.end() - 1) << endl;
}

void sum_avg(int *a, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    cout << "sum: " << sum << endl;
    cout << "avg: " << double(sum) / n << endl;
}

void my_sort(int *a, int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i];

        int j = i - 1;
        while (j >= 0 and a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

int main() {
    int n;
    cin >> n;

    int *a = create_arr(n);
    scan_arr(a, n);

    print_min_max(a, n);
    sum_avg(a, n);
    my_sort(a, n);
    print_arr(a, n);
    
    delete[] a;
}