#include <bits/stdc++.h>
using namespace std;

double **create_matrix(int m ,int n) {
    double **a = new double*[m];
    for (int i = 0; i < m; i++) {
        a[i] = new double[n];
    }
    return a;
}

double **copy_arr(double **a, int m ,int n) {
    double **cp = new double*[m];
    for (int i = 0; i < m; i++) {
        cp[i] = new double[n];
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cp[i][j] = a[i][j];
        }
    }
    return cp;
}

void scan_matrix(double **a, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
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

double trace(double **a, int m, int n) {
    int k = min(m, n);
    double trace = 0;
    for (int i = 0; i < k; i ++) {
        trace += a[i][i];
    }
    return trace;
}

double trace_secondary(double **a, int m, int n) {
    int k = min(m, n);
    double trace = 0.0;
    for (int i = 0; i < k; i ++) {
        trace += a[i][n - i - 1];
    }
    return trace;
}

double **transpose(double **a, int m, int n) {
    double **t = create_matrix(n, m);
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            t[j][i] = a[i][j]; 
        }
    }

    return t;
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

void jordan(double **a, int m, int n) {
    gauss(a, m, n);

    for (int i = 0; i < m; i++){
        if (a[i][i] != 0){
            double fact = a[i][i];
            for (int j = i; j < n; j++){
                a[i][j] /= fact;
            }
        }
    }

    for (int j = m - 1; j >= 0; j--){
        for (int i = j - 1; i >= 0; i--){
            if (a[j][j] != 0){
                double fact = a[i][j] / a[j][j];
                if (fact != 0) {
                    for (int k = j; k < n; k++){
                        a[i][k] -= fact*a[j][k];
                    }
                }
            }
        }
    }
}

double det(double **a, int m, int n) {
    double **cp = copy_arr(a, m, n);
    gauss(cp, m, n);
    double d = 1.0;
    for (int i = 0; i < m; i ++) {
        d *= cp[i][i];
    }
    delete_2d_matrix(cp, m);
    return d;
}

double **inverse_matrix(double **a, int m, int n) {
    if (det(a, m, n) == 0 || (m != n)) {
        cout << "invalid" << endl;
        return nullptr;
    }
    double **b = create_matrix(m, n*2);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n*2; j++) {
            if (j < n) {
                b[i][j] = a[i][j];
            }
            else {
                if (j == n + i) {
                    b[i][j] = 1.0; 
                }
                else {
                    b[i][j] = 0.0; 
                }
            }
        }
    }

    jordan(b, m, 2*n);

    double **c = create_matrix(m, n);
    
    for (int i = 0; i < m; i++) {
        for (int j = n; j < n*2; j++) {
            c[i][j - n] = b[i][j]; 
        }
    } 

    delete_2d_matrix(b, m);
    return c;
}

int main() {
    int m, n;
    cin >> m >> n;

    double **a = create_matrix(m, n);
    scan_matrix(a, m, n);

    cout << trace(a, m, n) << endl;
    cout << trace_secondary(a, m, n) << endl;

    double **t = create_matrix(m, n);
    t = transpose(a, m, n);
    print_matrix(t, n, m);

    double **a_1 = inverse_matrix(a, m, n); 
    print_matrix(a_1, m, n);

    delete_2d_matrix(a, m);
    delete_2d_matrix(t, m);
    delete_2d_matrix(a_1, m);
}