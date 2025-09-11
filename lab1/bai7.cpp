#include <bits/stdc++.h>
using namespace std;

int **create_matrix(int m ,int n) {
    int **a = new int*[m];
    for (int i = 0; i < m; i++) {
        a[i] = new int[n];
    }
    return a;
}

void scan_matrix(int **a, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
}

void print_matrix(int **a, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
} 

void delete_2d_matrix(int **a, int m) {
    for (int i = 0; i < m; i++) {
        delete[] a[i];
    }
    delete[] a;
}

int trace(int **a, int m, int n) {
    int k = min(m, n);
    int trace = 0;
    for (int i = 0; i < k; i ++) {
        trace += a[i][i];
    }
    return trace;
}

int **transpose(int **a, int m, int n) {
    int **t = create_matrix(n, m);
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            t[j][i] = a[i][j]; 
        }
    }

    delete_2d_matrix(a, m);
    return t;
}

int **multiply(int **a, int m, int n, int **b, int mb, int nb) {
    if (n != mb) {
        cout << "invalid" << endl;
        return nullptr;
    }
    
    int **c = create_matrix(m, n);
    for (int i = 0; i < m; i++){
        for (int j = 0; j < nb; j++){
            c[i][j] = 0;
            for (int k = 0; k < n; k++){
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}

int main() {
    int m, n;
    cin >> m >> n;

    int **a = create_matrix(m, n);
    scan_matrix(a, m, n);

    cout << trace(a, m, n) << endl;

    a = transpose(a, m, n);
    print_matrix(a, n, m);

    int mb, nb;
    cin >> mb, nb;
    int **b = create_matrix(mb, nb);
    scan_matrix(b, mb, nb);
    int **c = multiply(a, m, n, b, mb, nb);
    print_matrix(c, m, nb);

    delete_2d_matrix(a, m);
    delete_2d_matrix(b, mb);
    delete_2d_matrix(c, m);
}