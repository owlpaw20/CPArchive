#include <array>
#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;
using Matrix = array<array<int, 2>, 2>;

int n, m;

Matrix operator*(const Matrix &A, const Matrix &B) {
    Matrix C = {0, 0, 0, 0};
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                C[i][j] = (((i64)C[i][j] + (i64)A[i][k] * B[k][j]) % m + m) % m;
    return C;
}

Matrix power(Matrix A, int k) {
    Matrix B = {1, 0, 0, 1};
    while (k) {
        if (k & 1) B = B * A;
        A = A * A;
        k >>= 1;
    }
    return B;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    Matrix A = {1, 1, 1, 0};
    Matrix B = power(A, n + 2);

    cout << max(B[0][1] - 1, 0) << endl;
    return fflush(stdout), 0;
}
