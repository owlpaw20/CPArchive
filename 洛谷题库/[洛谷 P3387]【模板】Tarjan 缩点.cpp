#include <bits/stdc++.h>

using PII = std::pair<int, int>;

const int MAX_N = 10'005;

int N, M, a[MAX_N];
std::vector<PII> edges;
std::vector<std::vector<int>> gg;

int dfn[MAX_N], low[MAX_N], ts;
std::stack<int> stk;
bool instk[MAX_N];

int b[MAX_N], bel[MAX_N], color;

void Tarjan(int u) {
  dfn[u] = low[u] = ++ts;
  stk.push(u), instk[u] = true;

  for (int v : gg[u])
    if (!dfn[v]) Tarjan(v), low[u] = std::min(low[u], low[v]);
    else if (instk[v]) low[u] = std::min(low[u], dfn[v]);

  if (dfn[u] == low[u]) {
    ++color;
    int v;
    do instk[v = stk.top()] = false, bel[v] = color, b[color] += a[v], stk.pop();
    while (v != u);
  }
}

std::vector<std::vector<int>> gh;
int indeg[MAX_N], f[MAX_N];

void topological_sort() {
  std::queue<int> q;

  for (int i = 1; i <= color; ++i)
    if (!indeg[i])
      q.push(i), f[i] = b[i];

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v : gh[u]) {
      f[v] = std::max(f[v], f[u] + b[v]);
      if (!--indeg[v]) q.push(v);
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;
  gg.resize(N + 1), edges.resize(M + 1);

  for (int i = 1; i <= N; ++i) std::cin >> a[i];

  for (int i = 1, u, v; i <= M; ++i) {
    std::cin >> u >> v;
    gg[u].push_back(v);
    edges[i] = {u, v};
  }

  for (int i = 1; i <= N; ++i)
    if (!dfn[i])
      Tarjan(i);

  gh.resize(color + 1);

  for (int i = 1; i <= M; ++i) {
    auto [u, v] = edges[i];
    if (bel[u] != bel[v]) gh[bel[u]].push_back(bel[v]), ++indeg[bel[v]];
  }

  topological_sort();

  std::cout << *std::max_element(f + 1, f + color + 1) << '\n';
  return 0;
}
