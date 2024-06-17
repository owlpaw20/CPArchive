#pragma GCC optimize("O2,unroll-loops,inline")

#include <iostream>

using LL = long long;

const int MOD = 1e6 + 3;

template <typename intT, typename bufT = LL>
intT power(intT b, intT e, intT mod = MOD) {
  intT res = 1;
  while (e) {
    ((e & 1) && (res = (bufT)res * b % mod));
    b = (bufT)b * b % mod;
    e >>= 1;
  }
  return res;
}

int nCk(int n, int k) {
  if (k > n) return 0;
  int fz = 1, fm = 1;
  for (int i = 1, j = n; i <= k; ++i, --j)
    fz = (LL)fz * j % MOD, fm = (LL)fm * i % MOD;
  return (LL)fz * power(fm, MOD - 2) % MOD;
}

int Lucas(int n, int k) {
  if (n < MOD && k < MOD) return nCk(n, k);
  return (LL)Lucas(n / MOD, k / MOD) * nCk(n % MOD, k % MOD) % MOD;
}

void solve() {
  int N, L, R;
  std::cin >> N >> L >> R;
  std::cout << ((Lucas(R - L + N + 1, R - L + 1) - 1) % MOD + MOD) % MOD << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) solve();

  std::cout.flush();
  return 0;
}
