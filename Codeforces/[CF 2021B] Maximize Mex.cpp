#include <bits/stdc++.h>

const int MAX_N = 2e5 + 5;

int N, x;
int cnt[MAX_N];

void solve() {
  std::cin >> N >> x;
  memset(cnt, 0, sizeof(int) * (N + 1));
  for (int i = 1, x; i <= N; ++i) std::cin >> x, x <= N && ++cnt[x];

  for (int i = 0; i <= N; ++i) {
    if (!cnt[i]) return std::cout << i << '\n', void();
    if (cnt[i] > 1 && i + x <= N) cnt[i + x] += cnt[i] - 1, --cnt[i];
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) solve();

  return 0;
}
