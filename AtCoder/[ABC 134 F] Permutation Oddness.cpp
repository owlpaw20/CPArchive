#include <iostream>

using LL = long long;

const int MAX_N = 55;
const int MAX_K = MAX_N * MAX_N;
const int MOD = 1e9 + 7;

int N, K;
int f[MAX_N][MAX_N][MAX_K];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> K;

  f[0][0][0] = 1;

  for (int i = 1; i <= N; ++i)
    for (int j = 0; j <= i; ++j)
      for (int k = j * 2; k <= K; k += 2) {
        f[i][j][k] = ((LL)f[i][j][k] + (2LL * j + 1) * f[i - 1][j][k - j * 2]) % MOD;
        f[i][j][k] = ((LL)f[i][j][k] + (j + 1LL) * (j + 1) * f[i - 1][j + 1][k - j * 2] % MOD);
        (j > 0) && (f[i][j][k] = ((LL)f[i][j][k] + f[i - 1][j - 1][k - j * 2]) % MOD);
      }

  std::cout << f[N][0][K] % MOD << std::endl;
  return 0;
}
