#include <cstring>
#include <iostream>

using LL = long long;

const int MAX_N = 2e5 + 5;
const int MOD = 1e9 + 7;

template <typename intT, typename bufT = LL>
intT power(intT b, intT e, intT mod = MOD) {
  intT res = 1;
  for (; e; e >>= 1)
    ((e & 1) && (res = (bufT)res * b % mod)), b = (bufT)b * b % mod;
  return res;
}

void solve() {
  static int N, M, K, a[MAX_N];

  std::cin >> N >> M >> K;
  for (int i = 1; i <= N; ++i) std::cin >> a[i];

  int invalid = 0;
  int choose = 1, rest = power(K - 1, M);
  int rest_inv = power(K - 1, MOD - 2);

  for (int i = 0; i < N; ++i) {
    invalid = (invalid + (LL)choose * rest % MOD) % MOD;
    choose = (LL)choose * (M - i) % MOD * power(i + 1, MOD - 2) % MOD;
    rest = (LL)rest * rest_inv % MOD;
  }

  std::cout << ((power(K, M) - invalid) % MOD + MOD) % MOD << '\n';
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
