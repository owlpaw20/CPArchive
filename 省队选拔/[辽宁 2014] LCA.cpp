// 参考题解：https://www.luogu.com.cn/problem/solution/P4211 第一篇 by 紫钦

#include <tuple>
#include <vector>
#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;
using PII = pair<int, int>;
using QUERY = tuple<int, int, int, bool>;

const int N = 5e4 + 5;
const int MOD = 201314;

int n;
vector<QUERY> queries;
PII answers[N];

namespace TD {
  vector<int> graph[N];
  int fa[N], size[N], depth[N], pref[N];
  int dfn[N], top[N], timestamp;

  void DFS1(int u, int f = 0) {
    fa[u] = f;
    size[u] = 1;
    depth[u] = depth[f] + 1;

    for (int v : graph[u]) {
      if (v == f) continue;

      DFS1(v, u);
      size[u] += size[v];

      if (!pref[u] || size[pref[u]] < size[v])
        pref[u] = v;
    }
  }

  void DFS2(int u, int path_top) {
    top[u] = path_top;
    dfn[u] = ++timestamp;

    if (!pref[u]) return;

    DFS2(pref[u], path_top);
    for (int v : graph[u])
      if (v != fa[u] && v != pref[u])
        DFS2(v, v);
  }

  struct SegTree {
    struct {
      int l, r;
      int sum, tag;
    } node[N << 2];

    void pushup(int u) {
      node[u].sum = node[u << 1].sum + node[u << 1 | 1].sum;
    }

    void pushdown(int u) {
      auto &fa = node[u];
      auto &lc = node[u << 1];
      auto &rc = node[u << 1 | 1];

      if (fa.tag) {
        lc.tag = (lc.tag + fa.tag) % MOD;
        rc.tag = (rc.tag + fa.tag) % MOD;
        lc.sum = (lc.sum + (lc.r - lc.l + 1LL) * fa.tag) % MOD;
        rc.sum = (rc.sum + (rc.r - rc.l + 1LL) * fa.tag) % MOD;
        fa.tag = 0;
      }
    }

    void build(int u = 1, int l = 1, int r = n) {
      node[u].l = l;
      node[u].r = r;
      node[u].tag = 0;

      if (l == r)
        return (void)(node[u].sum = 0);

      int mid = (l + r) >> 1;

      build(u << 1, l, mid);
      build(u << 1 | 1, mid + 1, r);

      pushup(u);
    }

    void update(int u, int l, int r, int x) {
      int nl = node[u].l, nr = node[u].r;

      if (nl >= l && nr <= r) {
        node[u].tag = (node[u].tag + x) % MOD;
        node[u].sum = (node[u].sum + (nr - nl + 1LL) * x) % MOD;
        return;
      }

      pushdown(u);

      int mid = (nl + nr) >> 1;

      if (l <= mid) update(u << 1, l, r, x);
      if (r > mid) update(u << 1 | 1, l, r, x);

      pushup(u);
    }

    int query(int u, int l, int r) {
      int nl = node[u].l, nr = node[u].r;

      if (nl >= l && nr <= r)
        return node[u].sum;

      pushdown(u);

      int mid = (nl + nr) >> 1;
      int ret = 0;

      if (l <= mid) ret += query(u << 1, l, r);
      if (r > mid) ret += query(u << 1 | 1, l, r);

      return ret;
    }
  } SGT;

  void update_val_on_path(int u, int v, int x = 1) {
    while (top[u] != top[v]) {
      if (depth[top[u]] < depth[top[v]]) swap(u, v);
      SGT.update(1, dfn[top[u]], dfn[u], x);
      u = fa[top[u]];
    }

    if (depth[u] > depth[v]) swap(u, v);
    SGT.update(1, dfn[u], dfn[v], x);
  }

  int query_sum_of_path(int u, int v) {
    int ret = 0;

    while (top[u] != top[v]) {
      if (depth[top[u]] < depth[top[v]]) swap(u, v);
      ret = (ret + SGT.query(1, dfn[top[u]], dfn[u])) % MOD;
      u = fa[top[u]];
    }

    if (depth[u] > depth[v]) swap(u, v);
    ret = (ret + SGT.query(1, dfn[u], dfn[v])) % MOD;
    return ret;
  }
}  // namespace TD

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int q;
  cin >> n >> q;
  for (int i = 2, f; i <= n; i++) {
    cin >> f, f++;
    TD::graph[i].push_back(f);
    TD::graph[f].push_back(i);
  }

  TD::DFS1(1);
  TD::DFS2(1, 1);
  TD::SGT.build();

  // 由于单次查询的复杂度为 O(n (log n)^2)，所以将询问离线并采用差分处理
  for (int i = 1; i <= q; i++) {
    int l, r, x;
    cin >> l >> r >> x, l++, r++, x++;
    queries.emplace_back(l - 1, x, i, 0);
    queries.emplace_back(r, x, i, 1);
  }

  sort(queries.begin(), queries.end());

  int node = 0;
  for (auto [p, x, i, flag] : queries) {
    // 将被查询的所有端点与根节点的路径都打上标记
    // L 到 R 中所有点与 X 的 LCA 都一定在 X 到根的路径上
    // 则最终的答案就是 X 到 根的路径上所有标记之和
    while (node < p) TD::update_val_on_path(1, ++node);
    if (!flag)
      answers[i].second = TD::query_sum_of_path(1, x);
    else
      answers[i].first = TD::query_sum_of_path(1, x);
  }

  for (int i = 1; i <= q; i++)
    cout << (answers[i].first - answers[i].second + MOD) % MOD << endl;

  return fflush(stdout), 0;
}
