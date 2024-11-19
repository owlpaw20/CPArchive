#pragma GCC optimize("O2,unroll-loops")
#include <bits/stdc++.h>

using i64 = long long;

const int MAX_N = 3e5 + 5;

int N, M;
std::vector<std::vector<int>> gg;

int fa[20][MAX_N];
int dep[MAX_N], dfn[MAX_N], size[MAX_N], ts;

void DFS(int u) {
  size[u] = 1, dfn[u] = ++ts;
  dep[u] = dep[fa[0][u]] + 1;

  for (int v : gg[u]) {
    if (v == fa[0][u]) continue;
    fa[0][v] = u;
    for (int i = 1; i < 20; ++i) fa[i][v] = fa[i - 1][fa[i - 1][v]];
    DFS(v), size[u] += size[v];
  }
}

inline int qry_LCA(int u, int v) {
  if (dep[u] > dep[v]) std::swap(u, v);
  for (int i = 19; ~i; --i) (dep[fa[i][v]] >= dep[u]) && (v = fa[i][v]);
  if (v == u) return v;
  for (int i = 19; ~i; --i) (fa[i][v] != fa[i][u]) && (v = fa[i][v], u = fa[i][u]);
  return fa[0][u];
}

inline int kth_anc(int u, int k) {
  for (int i = 19; ~i; --i) (k >> i & 1) && (u = fa[i][u]);
  return u;
}

struct PathData {
  int u, v, lca, a, b;  // a, b 分别为 u, v 所在子树的根
  inline bool operator<(const PathData& rhs) const {
    if (dep[lca] != dep[rhs.lca]) return dep[lca] < dep[rhs.lca];
    if (lca != rhs.lca) return lca < rhs.lca;
    if (a != rhs.a) return a > rhs.a;
    return b > rhs.b;
  }
} pd[MAX_N];

struct SegT {
  i64 sum[MAX_N << 2];

  void upd(int x, int u = 1, int nl = 1, int nr = N) {
    if (nl == nr) return ++sum[u], void();
    int mid = (nl + nr) >> 1;
    if (x <= mid) upd(x, u << 1, nl, mid);
    else upd(x, u << 1 | 1, mid + 1, nr);
    sum[u] = sum[u << 1] + sum[u << 1 | 1];
  }

  i64 qry(int l, int r, int u = 1, int nl = 1, int nr = N) {
    if (nl >= l && nr <= r) return sum[u];
    int mid = (nl + nr) >> 1;
    i64 sum = 0;
    if (l <= mid) sum += qry(l, r, u << 1, nl, mid);
    if (r > mid) sum += qry(l, r, u << 1 | 1, mid + 1, nr);
    return sum;
  }
} T;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  gg.resize(N + 1);

  for (int i = 1, u, v; i < N; ++i) {
    std::cin >> u >> v;
    gg[u].push_back(v);
    gg[v].push_back(u);
  }

  DFS(1);

  std::cin >> M;

  for (int i = 1, u, v; i <= M; ++i) {
    std::cin >> u >> v;
    int lca = qry_LCA(u, v);
    int a = u == lca ? ++ts : kth_anc(u, dep[u] - dep[lca] - 1);  // 用子树的根 a 标记 u 所在子树
    int b = v == lca ? ++ts : kth_anc(v, dep[v] - dep[lca] - 1);  // 用子树的根 b 标记 v 所在子树
    if (a > b) std::swap(u, v), std::swap(a, b);                  // 按 a < b 的顺序存储到 PathData 中
    pd[i] = {u, v, lca, a, b};
  }

  // 对所有 PathData 进行排序
  std::sort(pd + 1, pd + M + 1);

  // path_cnt[i] 表示从 i 为根的子树里伸出来的路径数量
  std::vector<int> path_cnt(ts + 5);

  i64 ans = 0;

  for (int i = 1; i <= M; ++i) {
    int j = i;
    while (pd[j + 1].lca == pd[i].lca) ++j;  // 枚举得到所有 lca 相同的链

    // 已经枚举过的链的条数
    int cnt = 0;

    /**********
      先统计交于同一个 lca 的两条链：
      - 找到起点位于同一子树中的所有链 x
      - 计算已经枚举过的链可能与当前链 x 相交的链的数量
        - 即已经枚举过的链的数量 cnt 减去从当前链 x 另一端所在子树 b 伸出来的链的数量
      - 将所有链 x 计入从其两个端点子树伸出来的链的数量
      - 并将所有 x 计入当前子树已经考虑过的链的数量
    **********/

    for (int k = i; k <= j; ++k) {
      int l = k;
      while (l < j && pd[l + 1].a == pd[k].a) ++l;
      for (int m = k; m <= l; ++m) ans += cnt - path_cnt[pd[m].b];
      for (int m = k; m <= l; ++m) ++path_cnt[pd[m].a], ++path_cnt[pd[m].b];
      cnt += l - k + 1, k = l;
    }

    /**********
      再统计 lca 不同、交于当前，也就是较深的 lca 的两条链：
      - 先加上伸进 lca 子树中链的数量
      - 再减去伸进 a、b 子树中链的数量
        - 因为这些链端点与当前链的交点至少包含 a/b 和 lca 两个节点，不合题意
      - 最后将当前链的两个端点 u、v 更新到线段树中
    **********/

    for (int k = i; k <= j; ++k) {
      auto [u, v, lca, a, b] = pd[k];
      path_cnt[a] = path_cnt[b] = 0;  // 利用这次遍历清空先前对数组进行的修改
      ans += T.qry(dfn[lca], dfn[lca] + size[lca] - 1);
      if (a <= N) ans -= T.qry(dfn[a], dfn[a] + size[a] - 1);
      if (b <= N) ans -= T.qry(dfn[b], dfn[b] + size[b] - 1);
    }

    for (int k = i; k <= j; ++k)
      T.upd(dfn[pd[k].u]), T.upd(dfn[pd[k].v]);

    i = j;
  }

  std::cout << ans << '\n';
  return 0;
}
