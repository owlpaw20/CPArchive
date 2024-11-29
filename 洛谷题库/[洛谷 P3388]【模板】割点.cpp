#include <bits/stdc++.h>

const int MAX_N = 20'005;

int N, M;
std::vector<std::vector<int>> gg;

int dfn[MAX_N], low[MAX_N], ts;
bool is_cut[MAX_N];

bool Tarjan(int u, int fa) {
  dfn[u] = low[u] = ++ts;

  int cr_cnt = 0;

  for (int v : gg[u])
    if (!dfn[v]) {
      Tarjan(v, u);
      low[u] = std::min(low[u], low[v]);
      if (low[v] >= dfn[u]) u == fa ? ++cr_cnt : is_cut[u] = true;
    } else if (v != fa)
      low[u] = std::min(low[u], dfn[v]);

  return cr_cnt >= 2;
}

std::vector<int> cut;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;
  gg.resize(N + 1);

  for (int i = 1, u, v; i <= M; ++i) {
    std::cin >> u >> v;
    gg[u].push_back(v);
    gg[v].push_back(u);
  }

  for (int i = 1; i <= N; ++i)
    if (!dfn[i] && Tarjan(i, i))
      is_cut[i] = true;

  for (int i = 1; i <= N; ++i)
    if (is_cut[i])
      cut.push_back(i);

  std::cout << cut.size() << '\n';
  for (int c : cut) std::cout << c << ' ';
  return 0;
}
