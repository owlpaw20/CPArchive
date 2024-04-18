#include <queue>
#include <tuple>
#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <unordered_set>

#define endl '\n'

using namespace std;
using i64 = long long;
using PII = pair<int, int>;
using TUP = tuple<int, int, int, int>;

const int N = 1e5 + 5;

int n, m;

namespace LCA {
  vector<PII> graph[N];
  int fa[N][20], maxw[N][20];
  int depth[N];

  int log2(int x) {
    int exp = 0;
    while (x >>= 1)
      exp += 1;
    return exp;
  }

  void prep(int root) {
    queue<int> q;
    q.push(root);

    while (!q.empty()) {
      int u = q.front();
      q.pop();

      for (auto [v, w] : graph[u]) {
        if (depth[v]) continue;

        depth[v] = depth[u] + 1;
        maxw[v][0] = w, fa[v][0] = u;
        for (int j = 1; j <= log2(n); j++) {
          fa[v][j] = fa[fa[v][j - 1]][j - 1];
          maxw[v][j] = max(maxw[v][j - 1], maxw[fa[v][j - 1]][j - 1]);
        }

        q.push(v);
      }
    }
  }

  int query(int u, int v, int w) {
    if (depth[u] > depth[v]) swap(u, v);

    int ret = -1;

    for (int i = log2(n); i >= 0; i--)
      if (depth[fa[v][i]] >= depth[u]) {
        if (maxw[v][i] < w) ret = max(ret, maxw[v][i]);
        v = fa[v][i];
      }

    if (v == u) return ret;

    for (int i = log2(n); i >= 0; i--)
      if (fa[u][i] != fa[v][i]) {
        if (maxw[u][i] < w) ret = max(ret, maxw[u][i]);
        if (maxw[v][i] < w) ret = max(ret, maxw[v][i]);
        u = fa[u][i], v = fa[v][i];
      }

    if (maxw[u][0] < w) ret = max(ret, maxw[u][0]);
    if (maxw[v][0] < w) ret = max(ret, maxw[v][0]);
    return ret;
  }
}  // namespace LCA

namespace MST {
  vector<TUP> edges, edges2;
  unordered_set<int> used;

  namespace UnionFind {
    int fa[N];
    void init(int n) {
      iota(fa, fa + n + 1, 0);
    }
    int find(int x) {
      return x == fa[x] ? x : (fa[x] = find(fa[x]));
    }
    bool merge(int x, int y) {
      x = find(x), y = find(y);
      if (x == y) return false;
      return fa[x] = y, true;
    }
  }  // namespace UnionFind

  i64 Kruskal() {
    i64 ans = 0;
    int cnt = 0;
    UnionFind::init(n);

    for (size_t i = 0; i < edges.size(); i++) {
      if (cnt == n - 1) continue;
      auto [w, u, v, k] = edges[i];
      if (UnionFind::merge(u, v)) {
        used.insert(k);
        ans += w, cnt += 1;
        LCA::graph[u].emplace_back(v, w);
        LCA::graph[v].emplace_back(u, w);
      }
    }

    if (cnt != n - 1) return (1ULL << 63) - 1;
    return ans;
  }
}  // namespace MST

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;

  int idx = 0;
  for (int i = 0; i < m; i++) {
    int x, y, z;
    cin >> x >> y >> z;
    if (x == y) continue;
    MST::edges.emplace_back(z, x, y, idx++);
  }

  MST::edges2 = MST::edges;
  sort(MST::edges.begin(), MST::edges.end());

  i64 MST = MST::Kruskal();

  LCA::prep(1);

  i64 ans = (1ULL << 63) - 1;

  for (int i = 0; i < idx; i++)
    if (!MST::used.count(i)) {
      auto [w, u, v, k] = MST::edges2[i];
      int maxw = LCA::query(u, v, w);
      ans = min(ans, MST - maxw + w);
    }

  cout << ans << endl;
  return fflush(stdout), 0;
}
