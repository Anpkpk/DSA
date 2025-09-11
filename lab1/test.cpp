#include<bits/stdc++.h>

using namespace std;

void scan_arr(int *a, int n) {
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
}

void print_arr(int *a, int n) {
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }  
}

int *create_arr(int n) {
    int *a = new int[n];
    return a;
}

void insertion_sort(int *a, int *n) {
    cin >> *n;
    a = create_arr(*n);
    scan_arr(a, *n);

    for (int i = 1; i < *n; i++) {
        int key = a[i];

        int j = i - 1;
        while (j >= 0 and a[j] < key) {
            a[j + 1] = a[j];
            j -= 1;
        }
        a[j + 1] = key;
    }

    print_arr(a, *n);
    
}

int main() {
    int *n = new int;
    int *a = new int[*n];

    insertion_sort(a, n);

    delete n;
    delete[] a;
    return 0;
}

