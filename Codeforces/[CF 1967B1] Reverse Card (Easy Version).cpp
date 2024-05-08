#include <numeric>
#include <iostream>

using l64 = long long;

void solve() {
  int N, M;
  std::cin >> N >> M;

  l64 ans = 0;
  for (int i = 1; i <= M; ++i)
    ans += (N / i + 1) / i;

  std::cout << ans - 1 << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) solve();

  return fflush(stdout), 0;
}
