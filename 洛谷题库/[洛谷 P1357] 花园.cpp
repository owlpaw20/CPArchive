#include <cstring>
#include <iostream>

using LL = long long;

constexpr int MAX_N = 1 << 5;
constexpr int MOD = 1e9 + 7;

LL N;
int M, states, k;

struct Matrix {
  int mat[MAX_N][MAX_N];

  void unitize() {
    for (int i = 0; i < states; ++i)
      mat[i][i] = 1;
  }

  Matrix operator*(const Matrix& x) const {
    Matrix ret;
    for (int i = 0; i < states; ++i)
      for (int j = 0; j < states; ++j)
        for (int k = 0; k < states; ++k)
          ret.mat[i][j] = (ret.mat[i][j] + (LL)mat[i][k] * x.mat[k][j] % MOD) % MOD;
    return ret;
  }

  Matrix() { memset(mat, 0, sizeof mat); }
};

Matrix pow(Matrix A, LL b) {
  Matrix ret;
  ret.unitize();
  while (b) {
    if (b & 1) ret = ret * A;
    A = A * A;
    b >>= 1;
  }
  return ret;
}

int popcnt(int x) { return __builtin_popcount(x); }

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M >> k;
  states = 1 << M;

  Matrix trans;

  for (int state = 0; state < states; ++state) {
    if (popcnt(state) > k) continue;
    int pre_state_1 = state >> 1;
    int pre_state_2 = (state >> 1) | (1 << (M - 1));
    if (popcnt(pre_state_1) <= k) trans.mat[pre_state_1][state] = 1;
    if (popcnt(pre_state_2) <= k) trans.mat[pre_state_2][state] = 1;
  }

  Matrix res = pow(trans, N);

  int ans = 0;
  for (int i = 0; i < states; ++i)
    ans = (ans + res.mat[i][i]) % MOD;

  std::cout << ans << std::endl;
  return 0;
}
