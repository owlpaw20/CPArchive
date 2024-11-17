#include <bits/stdc++.h>

void solve() {
  int N, ans = 0;
  int p = -1, cnt = 1;

  std::cin >> N;

  for (int i = 1, x; i <= N; ++i, p = x) {
    std::cin >> x;
    if (x == p) ++cnt;
    else ans = std::max(ans, cnt), cnt = 1;
  }

  std::cout << N - std::max(ans, cnt) << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) solve();

  return 0;
}
