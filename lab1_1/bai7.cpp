#include <bits/stdc++.h>
using namespace std;

double **create_matrix(int m ,int n) {
    double **a = new double*[m];
    for (int i = 0; i < m; i++) {
        a[i] = new double[n];
    }
    return a;
}

void scan_matrix(double **a, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
}

void scan_vector(double *a, int n) {
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
}

void print_matrix(double **a, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
} 

void delete_2d_matrix(double **a, int m) {
    for (int i = 0; i < m; i++) {
        delete[] a[i];
    }
    delete[] a;
}

double **copy_arr(double **a, int n) {
    double **cp = new double*[n];
    for (int i = 0; i < n + 1; i++) {
        cp[i] = new double[n];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cp[i][j] = a[i][j];
        }
    }
    return cp;
}

void gauss(double **a, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            if (a[i][i] != 0) {
                double fact = a[j][i] / a[i][i];
                for (int k = i; k < n; k++){
                    a[j][k] -= fact * a[i][k];
                }
            }
        }
    }
}

int main() {
    int n;
    cin >> n;

    double **a = create_matrix(n, n);
    double *b = new double[n]; 

    scan_matrix(a, n, n);
    scan_vector(b, n);
    
    double **c = copy_arr(a, n);
    for (int i = 0; i < n; i++) {
        c[i][n] = b[i];
    }
    print_matrix(c, n, n + 1);

    gauss(c, n, n + 1);
    print_matrix(c, n, n + 1);
    
    delete_2d_matrix(a, n);
    delete_2d_matrix(c, n);
    delete[] b;
}