#include <tuple>
#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>

using TUP = std::tuple<int, int, int>;

const int MAX_V = 5e3 + 5;

int N, M;
std::vector<TUP> edges;

struct UnionFind {
  int fa[MAX_V];
  inline void init(int x) { std::iota(fa + 1, fa + x + 1, 1); }
  inline int find(int x) { return (x == fa[x]) ? x : (fa[x] = find(fa[x])); }
  inline bool merge(int x, int y) { return ((x = find(x)) != (y = find(y))) && (fa[x] = y, true); }
} dsu;

int Kruskal() {
  int cnt = 0, ans = 0;
  for (auto [w, u, v] : edges)
    if (cnt == N - 1) break;
    else if (dsu.merge(u, v)) ans += w, ++cnt;
  if (cnt == N - 1) return ans;
  return -1;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M, edges.resize(M), dsu.init(N + 1);
  for (auto& [w, u, v] : edges) std::cin >> u >> v >> w;

  std::sort(edges.begin(), edges.end());

  int ans = Kruskal();
  ans == -1 ? (std::cout << "orz") : (std::cout << ans);

  fflush(stdout);
  return 0;
}
