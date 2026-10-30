#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<long long>> Matrix;

Matrix add(const Matrix& A, const Matrix& B) {
    size_t n = A.size();
    Matrix C(n, vector<long long>(n));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

Matrix sub(const Matrix& A, const Matrix& B) {
    size_t n = A.size();
    Matrix C(n, vector<long long>(n));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

Matrix standard_mult(const Matrix& A, const Matrix& B) {
    size_t n = A.size();
    Matrix C(n, vector<long long>(n, 0));
    for (size_t i = 0; i < n; ++i) {
        for (size_t k = 0; k < n; ++k) {
            for (size_t j = 0; j < n; ++j) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

Matrix strassen(const Matrix& A, const Matrix& B) {
    size_t n = A.size();
    if (n <= 2) {
        return standard_mult(A, B);
    }

    size_t k = n / 2;
    Matrix a11(k, vector<long long>(k)), a12(k, vector<long long>(k)),
           a21(k, vector<long long>(k)), a22(k, vector<long long>(k));
    Matrix b11(k, vector<long long>(k)), b12(k, vector<long long>(k)),
           b21(k, vector<long long>(k)), b22(k, vector<long long>(k));

    for (size_t i = 0; i < k; ++i) {
        for (size_t j = 0; j < k; ++j) {
            a11[i][j] = A[i][j];
            a12[i][j] = A[i][j + k];
            a21[i][j] = A[i + k][j];
            a22[i][j] = A[i + k][j + k];

            b11[i][j] = B[i][j];
            b12[i][j] = B[i][j + k];
            b21[i][j] = B[i + k][j];
            b22[i][j] = B[i + k][j + k];
        }
    }

    Matrix m1 = strassen(add(a11, a22), add(b11, b22));
    Matrix m2 = strassen(add(a21, a22), b11);
    Matrix m3 = strassen(a11, sub(b12, b22));
    Matrix m4 = strassen(a22, sub(b21, b11));
    Matrix m5 = strassen(add(a11, a12), b22);
    Matrix m6 = strassen(sub(a21, a11), add(b11, b12));
    Matrix m7 = strassen(sub(a12, a22), add(b21, b22));

    Matrix c11 = add(sub(add(m1, m4), m5), m7);
    Matrix c12 = add(m3, m5);
    Matrix c21 = add(m2, m4);
    Matrix c22 = add(add(sub(m1, m2), m3), m6);

    Matrix C(n, vector<long long>(n));
    for (size_t i = 0; i < k; ++i) {
        for (size_t j = 0; j < k; ++j) {
            C[i][j] = c11[i][j];
            C[i][j + k] = c12[i][j];
            C[i + k][j] = c21[i][j];
            C[i + k][j + k] = c22[i][j];
        }
    }
    return C;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 0;
    if (!(cin >> n)) return 0;

    // Next power of 2
    size_t m = 1;
    while (m < static_cast<size_t>(n)) m <<= 1;

    Matrix A(m, vector<long long>(m, 0));
    Matrix B(m, vector<long long>(m, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> A[static_cast<size_t>(i)][static_cast<size_t>(j)];
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> B[static_cast<size_t>(i)][static_cast<size_t>(j)];
        }
    }

    Matrix C = strassen(A, B);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) cout << " ";
            cout << C[static_cast<size_t>(i)][static_cast<size_t>(j)];
        }
        cout << "\n";
    }

    return 0;
}
