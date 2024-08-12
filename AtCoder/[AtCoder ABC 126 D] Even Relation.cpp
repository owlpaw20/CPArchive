#include <bits/stdc++.h>

using PII = std::pair<int, int>;

const int MAX_N = 1e5 + 5;

std::random_device rd;
std::mt19937 gen(rd());

int N;
std::vector<PII> g[MAX_N];

int c[MAX_N];

void DFS(int u) {
  for (auto [v, w] : g[u]) {
    if (c[v] != -1) continue;
    c[v] = c[u] ^ (w % 2);
    DFS(v);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;

  for (int i = 1, u, v, w; i < N; ++i) {
    std::cin >> u >> v >> w;
    g[u].emplace_back(v, w);
    g[v].emplace_back(u, w);
  }

  memset(c, -1, sizeof(int) * (N + 1));

  int root = gen() % N + 1;
  c[root] = 0, DFS(root);

  for (int i = 1; i <= N; ++i) std::cout << c[i] << '\n';

  std::cout.flush();
  return 0;
}
