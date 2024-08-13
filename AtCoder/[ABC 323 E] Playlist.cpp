#include <bits/stdc++.h>

const int MAX_N = 1e3 + 5;
const int MAX_V = 1e4 + 5;
const int MOD = 998'244'353;

using LL = long long;

int power(int b, int e, int mod = MOD) {
  int res = 1;
  for (; e; e >>= 1) {
    if (e & 1) res = (LL)res * b % mod;
    b = (LL)b * b % mod;
  }
  return res;
}

int N, x, t[MAX_N], f[MAX_V];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> x;
  for (int i = 1; i <= N; ++i) std::cin >> t[i];

  int inv = power(N, MOD - 2);

  f[0] = 1;

  for (int i = 0; i <= x; ++i)
    for (int j = 1; j <= N; ++j)
      if (i >= t[j])
        f[i] = (f[i] + (LL)f[i - t[j]] * inv) % MOD;

  int sum = std::accumulate(f + std::max(0, x - t[1] + 1), f + x + 1, 0LL) % MOD;
  std::cout << (LL)sum * inv % MOD << std::flush;
  return 0;
}
