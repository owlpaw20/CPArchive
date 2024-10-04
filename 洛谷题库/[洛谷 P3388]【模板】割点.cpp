#include <bits/stdc++.h>

const int MAX_N = 2e4 + 5;

int N, M;
std::vector<std::vector<int>> g;

int dfn[MAX_N], low[MAX_N], ts, cr_cnt;
bool cut[MAX_N];

void Tarjan(int u, int fa) {
  dfn[u] = low[u] = ++ts;

  for (int v : g[u]) {
    if (!dfn[v]) {
      Tarjan(v, u);
      low[u] = std::min(low[u], low[v]);
      if (low[v] >= dfn[u]) u == fa ? ++cr_cnt : cut[u] = true;
    } else if (v != fa)
      low[u] = std::min(low[u], dfn[v]);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;
  g.resize(N + 1);

  while (M--) {
    static int u, v;
    std::cin >> u >> v;
    g[u].push_back(v), g[v].push_back(u);
  }

  for (int i = 1; i <= N; ++i) {
    if (dfn[i]) continue;
    cr_cnt = 0;  // 根节点的子节点数
    Tarjan(i, i);
    if (cr_cnt >= 2) cut[i] = true;
  }

  std::cout << std::accumulate(cut + 1, cut + N + 1, 0) << '\n';

  for (int i = 1; i <= N; ++i)
    if (cut[i])
      std::cout << i << ' ';

  std::cout.flush();
  return 0;
}
