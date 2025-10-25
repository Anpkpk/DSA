#include <bits/stdc++.h>

using namespace std;

int *merge(int *a, int *b, int m, int n) {
    int *c = new int[m + n];

    int i = 0, l = 0, r = 0;

    while (l < m && r < n) {
        if (a[l] <  b[r]){
            c[i] = a[l];
            i++; l++;
        }
        else {
            c[i] = b[r];
            r++; i++;
        }
    } 

    while (l < m) {
        c[i] = a[l];
        i++; l++;
    }

    while (r < n) {
        c[i] = b[r];
        i++; r++;
    }
    return c;
}

int main() {
    int a[4] = {1, 3, 5, 7};
    int b[4] = {2, 4, 6, 8};

    int *c = merge(a, b, 4, 4); 
    for (int i = 0; i < 8; i++) {
        cout << c[i] << " "; 
    }

    delete[] c;
}