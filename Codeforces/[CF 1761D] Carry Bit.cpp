#include <cmath>
#include <iostream>

using LL = long long;

constexpr int MAX_N = 1e6 + 5;
constexpr int MOD = 1e9 + 7;

int N, k;
int fac[MAX_N] = {1}, inv[MAX_N] = {1};
int exp3[MAX_N] = {1};

template <typename intT, typename bufT = LL>
intT power(intT b, intT e, intT mod = MOD) {
  intT res = 1;
  for (; e; e >>= 1)
    ((e & 1) && (res = (bufT)res * b % mod)), b = (bufT)b * b % mod;
  return res;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> k;

  if (k == 0)
    return std::cout << power(3, N) << std::endl, 0;

  for (int i = 1; i <= N; ++i) {
    fac[i] = (LL)fac[i - 1] * i % MOD;
    inv[i] = power(fac[i], MOD - 2);
    exp3[i] = 3LL * exp3[i - 1] % MOD;
  }

  auto nCk = [&](int n, int k) -> int {
    if (k > n) return 0;
    return (LL)fac[n] * inv[k] % MOD * inv[n - k] % MOD;
  };

  int ans = 0;
  for (int q = 0; q <= N + 1; ++q) {
    static LL p;
    p = exp3[N - q + 1];
    p = p * nCk(k - 1, (q >> 1) - 1) % MOD;
    p = p * nCk(N - k, (((q + 1) >> 1) - 1)) % MOD;
    ans = (p + ans) % MOD;
  }

  std::cout << ans << std::endl;
  return 0;
}
