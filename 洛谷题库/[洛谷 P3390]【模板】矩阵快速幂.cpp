#include <vector>
#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;
using Matrix = vector<vector<int>>;

const int MOD = 1e9 + 7;

int n;
i64 k;
Matrix A;

Matrix operator*(const Matrix &A, const Matrix &B) {
    Matrix ret(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                ret[i][j] = (((i64)ret[i][j] + (i64)A[i][k] * B[k][j]) % MOD + MOD) % MOD;
    return ret;
}

Matrix power(Matrix A, i64 k) {
    Matrix ret(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) ret[i][i] = 1;

    while (k) {
        if (k & 1) ret = ret * A;
        A = A * A;
        k >>= 1;
    }

    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    A.resize(n, vector<int>(n, 0));

    for (vector<int> &row : A)
        for (int &num : row)
            cin >> num;

    Matrix Ak = power(A, k);

    for (vector<int> row : Ak) {
        for (int num : row)
            cout << num << ' ';
        cout << endl;
    }

    return fflush(stdout), 0;
}
