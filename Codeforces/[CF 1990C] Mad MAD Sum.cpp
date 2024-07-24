#include <cstring>
#include <numeric>
#include <iostream>

using LL = long long;

constexpr int MAX_N = 2e5 + 5;

int N;
int a[MAX_N];

void action() {
  static bool seen[MAX_N];
  memset(seen, 0, sizeof(bool) * (N + 1));

  int max = 0;
  for (int i = 1; i <= N; ++i) {
    if (seen[a[i]]) max = std::max(max, a[i]);
    seen[a[i]] = true;
    a[i] = max;
  }
}

void solve() {
  std::cin >> N;
  for (int i = 1; i <= N; ++i) std::cin >> a[i];

  LL ans = 0;
  ans += std::accumulate(a + 1, a + N + 1, 0LL), action();
  ans += std::accumulate(a + 1, a + N + 1, 0LL), action();
  for (int i = 1; i <= N; ++i) ans += (N - i + 1LL) * a[i];

  std::cout << ans << '\n';
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
