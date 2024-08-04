#include <bits/stdc++.h>

const int MAX_N = 1e6 + 5;

int N, M, T, t, a[4][MAX_N], vis[MAX_N];

void operate(int times) {
  for (int t = 1, bp = 0; memset(vis, 0, sizeof(int) * (N + 1)), t <= times; ++t, bp = 0) {
    for (int i = 1; i <= N; ++i) (a[t - 1][i] <= N) && ++vis[a[t - 1][i]];
    for (int i = 0; i <= N && (vis[i] ? true : (bp = i, false)); ++i);
    for (int i = 1; i <= N; ++i) a[t][i] = (a[t - 1][i] < bp && vis[a[t - 1][i]] == 1) ? a[t - 1][i] : bp;
  }
}

void solve() {
  for (int i = 1; i <= N ? true : (operate(t = std::min(M, M % 2 == 0 ? 2 : 3)), false); ++i) std::cin >> a[0][i];
  for (int i = 1; i <= N; ++i) std::cout << a[t][i] << (i == N ? '\n' : ' ');
}

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cin >> T;
  while (T--) std::cin >> N >> M, solve();
  return std::cout.flush(), 0;
}
