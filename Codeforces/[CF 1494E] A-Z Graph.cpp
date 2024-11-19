#include <bits/stdc++.h>

using PII = std::pair<int, int>;

int N, M;
std::vector<std::unordered_map<int, char>> g;
std::set<PII> same, diff;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;
  g.resize(N + 1);

  while (M--) {
    char type, c;
    int u, v;

    std::cin >> type;

    switch (type) {
      case '+': {
        std::cin >> u >> v >> c;
        g[u].emplace(v, c);
        if (!g[v].count(u)) continue;
        (g[v][u] == c ? same : diff).insert(std::minmax(u, v));
      } break;

      case '-': {
        std::cin >> u >> v;
        c = g[u][v], g[u].erase(v);
        if (!g[v].count(u)) continue;
        (g[v][u] == c ? same : diff).erase(std::minmax(u, v));
      } break;

      case '?': {
        std::cin >> v;
        std::cout << ((v & 1 ? diff.empty() && same.empty() : same.empty()) ? "NO\n" : "YES\n");
      } break;
    }
  }

  return 0;
}
