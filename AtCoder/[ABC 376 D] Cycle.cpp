#include <bits/stdc++.h>

using PII = std::pair<int, int>;

const int MAX_N = 2e5 + 5;

int N, M;
std::vector<std::vector<int>> g;

bool vis[MAX_N];

int BFS(int st = 1) {
  std::queue<PII> q;
  q.emplace(st, 0);

  while (!q.empty()) {
    auto [u, d] = q.front();
    q.pop();

    if (u == 1 && d) return d;
    if (vis[u]) continue;
    vis[u] = true;

    for (int v : g[u]) q.emplace(v, d + 1);
  }

  return -1;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;
  g.resize(N + 1);

  while (M--) {
    static int u, v;
    std::cin >> u >> v;
    g[u].push_back(v);
  }

  std::cout << BFS() << std::flush;
  return 0;
}
