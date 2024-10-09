#include <bits/stdc++.h>

constexpr int MAX_N = 2e5 + 5;

int N, M, q;
int a[MAX_N], b[MAX_N];
bool vis[MAX_N];

// 核心思路：已经播放过 PPT 的人可以站到任何地方，所以不用再考虑

void solve() {
  std::cin >> N >> M >> q;
  memset(vis, 0, sizeof(int) * (N + 1));
  for (int i = 1; i <= N; ++i) std::cin >> a[i];
  for (int i = 1; i <= M; ++i) std::cin >> b[i];

  for (int i = 1, j = 1; i <= M; ++i) {
    if (vis[b[i]]) continue;
    if (j <= N && a[j] == b[i]) vis[a[j++]] = true;
    else return puts("TIDAK"), void();
  }

  puts("YA");
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) solve();

  return 0;
}
