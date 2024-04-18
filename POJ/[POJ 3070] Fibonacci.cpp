#include <array>
#include <iostream>

#define endl '\n'

using namespace std;
using Matrix = array<array<int, 2>, 2>;

const int MOD = 1e4;

Matrix operator*(const Matrix &A, const Matrix &B) {
  Matrix C = {0, 0, 0, 0};
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++)
      for (int k = 0; k < 2; k++)
        C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
  return C;
}

Matrix power(Matrix A, int k) {
  Matrix B = {0, 0, 0, 0};
  B[0][0] = B[1][1] = 1;

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

  int x;
  while (cin >> x, x != -1) {
    Matrix A = {1, 1, 1, 0};
    Matrix B = power(A, x);
    cout << B[0][1] << endl;
  }

  return fflush(stdout), 0;
}
