#pragma GCC optimize("O2,unroll-loops,inline")
#include <bits/stdc++.h>

using i64 = long long;
using PII = std::pair<int, int>;

const int MAX_N = 2e5 + 5;

int N, M;
std::vector<std::vector<PII>> g;

struct Edge {
  int u, v, w, id;
  bool operator<(const Edge& t) const { return w < t.w; }
} edge[MAX_N];

int pa[MAX_N];
int find(int x) { return pa[x] == x ? x : pa[x] = find(pa[x]); }

std::unordered_set<int> in_mst;

i64 Kruskal() {
  std::sort(edge + 1, edge + M + 1);
  std::iota(pa, pa + N + 1, 0);

  i64 mst = 0;

  for (int i = 1; i <= M; ++i) {
    if ((int)in_mst.size() == N - 1) break;

    auto [u, v, w, id] = edge[i];
    int pu = find(u), pv = find(v);
    if (pu == pv) continue;
    pa[pu] = pv;

    in_mst.insert(id), mst += w;
    g[u].emplace_back(v, w);
    g[v].emplace_back(u, w);
  }

  assert((int)in_mst.size() == N - 1 && mst);
  return mst;
}

int dep[MAX_N];
int fa[20][MAX_N];
int maxw[20][MAX_N];

void BFS(int st) {
  std::queue<int> q;
  dep[st] = 1;
  q.push(st);

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (auto [v, w] : g[u]) {
      if (dep[v]) continue;

      fa[0][v] = u;
      maxw[0][v] = w;
      dep[v] = dep[u] + 1;

      for (int i = 1; i < 20; ++i) {
        fa[i][v] = fa[i - 1][fa[i - 1][v]];
        maxw[i][v] = std::max(maxw[i - 1][v], maxw[i - 1][fa[i - 1][v]]);
      }

      q.push(v);
    }
  }
}

int qry_maxw(int u, int v) {
  if (dep[u] > dep[v]) std::swap(u, v);

  int ret = 0;

  for (int i = 19; ~i; --i)
    if (dep[fa[i][v]] >= dep[u])
      ret = std::max(ret, maxw[i][v]), v = fa[i][v];

  if (u == v) return ret;

  for (int i = 19; ~i; --i)
    if (fa[i][v] != fa[i][u])
      ret = std::max({ret, maxw[i][v], maxw[i][u]}), v = fa[i][v], u = fa[i][u];

  ret = std::max({ret, maxw[0][v], maxw[0][u]});
  assert(fa[0][v] == fa[0][u] && ret);
  return ret;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;
  g.resize(N + 1);

  if (!M) return 0;

  for (int i = 1, u, v, w; i <= M; ++i) {
    std::cin >> u >> v >> w;
    edge[i] = {u, v, w, i};
  }

  i64 mst = Kruskal();
  BFS(1);

  std::sort(edge + 1, edge + M + 1, [&](auto x, auto y) { return x.id < y.id; });

  for (int i = 1; i <= M; ++i)
    if (in_mst.count(i)) std::cout << mst << '\n';
    else std::cout << mst - qry_maxw(edge[i].u, edge[i].v) + edge[i].w << '\n';

  std::cout.flush();
  return 0;
}
