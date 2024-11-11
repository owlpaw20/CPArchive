#include <bits/stdc++.h>

using i64 = long long;

const int MAX_N = 1e6 + 5;

int N;
std::vector<std::vector<int>> g;

int size[MAX_N], dep[MAX_N];
i64 f[MAX_N];

void DFS1(int u, int fa) {
  size[u] = 1;
  dep[u] = dep[fa] + 1;

  for (int v : g[u])
    if (v != fa)
      DFS1(v, u), size[u] += size[v];
}

void DFS2(int u, int fa) {
  for (int v : g[u])
    if (v != fa)
      f[v] = f[u] + N - 2 * size[v], DFS2(v, u);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  g.resize(N + 1);

  for (int i = 1, u, v; i < N; ++i) {
    std::cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  dep[0] = -1;
  DFS1(1, 0);

  for (int i = 1; i <= N; ++i) f[1] += dep[i];
  DFS2(1, 0);

  std::cout << std::max_element(f + 1, f + N + 1) - f << '\n';
  return 0;
}
