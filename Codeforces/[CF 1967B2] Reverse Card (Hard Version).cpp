#include <cmath>
#include <numeric>
#include <iostream>

using l64 = long long;

void solve() {
  int N, M;
  std::cin >> N >> M;

  int a = sqrt(N), b = sqrt(M);
  l64 ans = 0;

  for (int i = 1; i <= a; ++i)
    for (int j = 1; j <= b; ++j)
      if (std::gcd(i, j) == 1)
        ans += std::min(N / i, M / j) / (i + j);

  std::cout << ans << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) solve();

  return fflush(stdout), 0;
}
