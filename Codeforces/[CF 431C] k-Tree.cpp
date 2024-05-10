#pragma GCC optimize("O2,unroll-loops,inline")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>

const int MAX_N = 1e2 + 5;
const int MOD = 1e9 + 7;

int N, K, D;
int f[MAX_N];  // 满足限制的方案数
int g[MAX_N];  // 不满足限制的方案数

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> K >> D;

  g[0] = 1;

  for (int i = 1; i <= N; ++i)
    for (int j = 1; j <= std::min(i, K); ++j) {
      (f[i] += f[i - j]) %= MOD;
      if (j < D) (g[i] += g[i - j]) %= MOD;
      else (f[i] += g[i - j]) %= MOD;
    }

  std::cout << f[N] << '\n';
  return fflush(stdout), 0;
}
