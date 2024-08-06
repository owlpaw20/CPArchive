#include <bits/stdc++.h>

using i64 = long long;
using i128 = __int128_t;

const int MAX_N = 12;

int N, a[MAX_N], b[MAX_N];

void ex_gcd(i64 a, i64 b, i64 &x, i64 &y) {
  if (!b) return x = 1, y = 0, void();
  ex_gcd(b, a % b, y, x), y -= a / b * x;
}

i64 CRT() {
  i64 prod = std::accumulate(b + 1, b + N + 1, 1LL, std::multiplies()), ans = 0;
  for (int i = 1; i <= N; ++i) {
    i64 m = prod / b[i], x = 0, y = 0;
    ex_gcd(m, b[i], x, y);
    ans = (ans + (i128)m * x * a[i] % prod) % prod;
  }
  return (ans % prod + prod) % prod;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  for (int i = 1; i <= N; ++i) std::cin >> a[i];
  for (int i = 1; i <= N; ++i) std::cin >> b[i];

  std::cout << CRT() << std::flush;
  return 0;
}
