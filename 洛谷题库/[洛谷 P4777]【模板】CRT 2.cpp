#include <numeric>
#include <iostream>

using LL = long long;
using LLL = __int128_t;

int N;

void exgcd(LL a, LL b, LL& x, LL& y) {
  if (b == 0) return x = 1, y = 0, void();
  exgcd(b, a % b, y, x);
  y -= a / b * x;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;

  LL m1 = 0, r1 = 0;
  for (int i = 1; i <= N; ++i) {
    LL m2, r2;
    std::cin >> m2 >> r2;

    if (i == 1) {
      m1 = m2;
      r1 = r2;
      continue;
    }

    LL gcd = std::gcd(m1, m2);
    LL lcm = (LLL)m1 * m2 / gcd;

    LL x = 0, y = 0;
    exgcd(m1 / gcd, m2 / gcd, x, y);

    r1 = ((r1 + (LLL)(r2 - r1) / gcd * x * m1) % lcm + lcm) % lcm;
    m1 = lcm;
  }

  std::cout << r1 << std::endl;
  return 0;
}
