// 推导过程见 https://www.acwing.com/solution/content/47979/

#pragma GCC optimize("O2,unroll-loops,inline")

#include <cmath>
#include <numeric>
#include <iostream>

using LL = long long;

const LL INF = 1e18;

template <typename intT, typename bufT = __int128_t>
intT power(intT b, intT e, intT mod) {
  intT res = 1;
  while (e) {
    ((e & 1) && (res = (bufT)res * b % mod));
    b = (bufT)b * b % mod;
    e >>= 1;
  }
  return res;
}

LL phi(LL x) {
  LL ret = x;

  for (int i = 2, lmt = sqrt(x); i <= lmt; ++i)
    if (x % i == 0) {
      ret = ret / i * (i - 1);
      while (x % i == 0) x /= i;
    }

  if (x != 1) ret = ret / x * (x - 1);
  return ret;
}

void solve(int L, int TC) {
  int gcd = std::gcd<LL, LL>(L, 8);

  LL C = 9LL * L / gcd, ans = INF;
  LL phi_C = phi(C), sqrt_phi_C = sqrt(phi_C);

  if (C % 2 == 0 || C % 5 == 0)
    ans = 0;
  else {
    for (int i = 1; i <= sqrt_phi_C; ++i)
      if (phi_C % i == 0) {
        if (power<LL>(10, i, C) == 1) ans = std::min(ans, (LL)i);
        if (power<LL>(10, phi_C / i, C) == 1) ans = std::min(ans, phi_C / i);
      }
  }

  printf("Case %d: %lld\n", TC, ans);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int L, TC = 0;
  while (std::cin >> L, L) solve(L, ++TC);

  return fflush(stdout), 0;
}
