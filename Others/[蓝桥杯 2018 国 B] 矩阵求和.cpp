#include <bits/stdc++.h>

using i64 = long long;

const int MAX_N = 1e7 + 5;
const int MOD = 1e9 + 7;

int N;
i64 f[MAX_N];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;

  int ans = 0;

  for (int i = N; i; --i) {
    f[i] = (i64)(N / i) * (N / i);
    for (int j = 2; i * j <= N; ++j) f[i] -= f[i * j];
    ans = (ans + f[i] % MOD * i % MOD * i % MOD) % MOD;
  }

  std::cout << ans << std::flush;
  return 0;
}
