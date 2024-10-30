#include <bits/stdc++.h>

using i64 = long long;

int N;
i64 p, q, r, f, g, h;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> p >> q >> r;
  f = g = h = std::numeric_limits<i64>::min();

  for (int i = 1, x; i <= N; ++i) {
    std::cin >> x;
    f = std::max(f, p * x);
    g = std::max(g, f + q * x);
    h = std::max(h, g + r * x);
  }

  std::cout << h << std::flush;
  return 0;
}
