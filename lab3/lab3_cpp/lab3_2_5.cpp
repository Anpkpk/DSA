#include <bits/stdc++.h>

using namespace std;
using Matrix = vector<vector<double>>;

Matrix add(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix C(n, vector<double>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

Matrix sub(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix C(n, vector<double>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

Matrix multiplyRec(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix C(n, vector<double>(n, 0.0));

    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    int m = n / 2;

    Matrix A11(m, vector<double>(m)), A12(m, vector<double>(m)),
           A21(m, vector<double>(m)), A22(m, vector<double>(m));
    Matrix B11(m, vector<double>(m)), B12(m, vector<double>(m)),
           B21(m, vector<double>(m)), B22(m, vector<double>(m));

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + m];
            A21[i][j] = A[i + m][j];
            A22[i][j] = A[i + m][j + m];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + m];
            B21[i][j] = B[i + m][j];
            B22[i][j] = B[i + m][j + m];
        }
    }

    Matrix C11 = add(multiplyRec(A11, B11), multiplyRec(A12, B21));
    Matrix C12 = add(multiplyRec(A11, B12), multiplyRec(A12, B22));
    Matrix C21 = add(multiplyRec(A21, B11), multiplyRec(A22, B21));
    Matrix C22 = add(multiplyRec(A21, B12), multiplyRec(A22, B22));

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            C[i][j] = C11[i][j];
            C[i][j + m] = C12[i][j];
            C[i + m][j] = C21[i][j];
            C[i + m][j + m] = C22[i][j];
        }
    }

    return C;
}

Matrix naiveMult(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix C(n, vector<double>(n, 0));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

Matrix strassen(const Matrix &A, const Matrix &B) {
    int n = A.size();
    if (n <= 2) return naiveMult(A, B);

    int k = n / 2;

    Matrix A11(k, vector<double>(k)), A12(k, vector<double>(k)),
           A21(k, vector<double>(k)), A22(k, vector<double>(k));
    Matrix B11(k, vector<double>(k)), B12(k, vector<double>(k)),
           B21(k, vector<double>(k)), B22(k, vector<double>(k));

    for (int i = 0; i < k; ++i)
        for (int j = 0; j < k; ++j) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }

    // S1..S10
    Matrix S1  = sub(B12, B22);
    Matrix S2  = add(A11, A12);
    Matrix S3  = add(A21, A22);
    Matrix S4  = sub(B21, B11);
    Matrix S5  = add(A11, A22);
    Matrix S6  = add(B11, B22);
    Matrix S7  = sub(A12, A22);
    Matrix S8  = add(B21, B22);
    Matrix S9  = sub(A11, A21);
    Matrix S10 = add(B11, B12);

    // P1..P7
    Matrix P1 = strassen(A11, S1);
    Matrix P2 = strassen(S2, B22);
    Matrix P3 = strassen(S3, B11);
    Matrix P4 = strassen(A22, S4);
    Matrix P5 = strassen(S5, S6);
    Matrix P6 = strassen(S7, S8);
    Matrix P7 = strassen(S9, S10);

    // C11..C22
    Matrix C11 = add(sub(add(P5, P4), P2), P6);
    Matrix C12 = add(P1, P2);
    Matrix C21 = add(P3, P4);
    Matrix C22 = sub(sub(add(P5, P1), P3), P7);

    Matrix C(n, vector<double>(n));
    for (int i = 0; i < k; ++i)
        for (int j = 0; j < k; ++j) {
            C[i][j]         = C11[i][j];
            C[i][j + k]     = C12[i][j];
            C[i + k][j]     = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }

    return C;
}

void printMatrix(const Matrix &A) {
    for (int i = 0; i < A.size(); ++i) {
            for (int j = 0; j < A[i].size(); ++j) {
                cout << A[i][j] << " ";
            }
            cout << endl;
        }
}

int main() {
    Matrix A = {{1, 2, 3, 4},
                {5, 6, 7, 8},
                {9, 1, 2, 3},
                {4, 5, 6, 7}};

    Matrix B = {{8, 7, 6, 5},
                {4, 3, 2, 1},
                {9, 8, 7, 6},
                {5, 4, 3, 2}};

    Matrix C_naive = naiveMult(A, B);
    Matrix C_rec = multiplyRec(A, B);
    Matrix C_strassen = strassen(A, B);
    

    printMatrix(C_naive);
    cout << endl;
    
    printMatrix(C_rec);
    cout << endl;
    
    printMatrix(C_strassen);
    cout << endl;
}
