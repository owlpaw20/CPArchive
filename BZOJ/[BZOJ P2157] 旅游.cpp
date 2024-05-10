#include <tuple>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>

using TUP = std::tuple<int, int, int>;

const int MAX_V = 2e5 + 5;
const int MAX_E = 4e5 + 5;
const int INF = 1e9;

int N;
int ed[MAX_E], nx[MAX_E], wt[MAX_E], head[MAX_V], idx;

void connect(int u, int v, int w) {
  ed[idx] = v;
  wt[idx] = w;
  nx[idx] = head[u];
  head[u] = idx++;
}

int fa[MAX_V], size[MAX_V], pref[MAX_V], depth[MAX_V], tmp[MAX_V];
int dfn[MAX_V], top[MAX_V], w[MAX_V], timestamp;

void DFS1(int u, int p) {
  fa[u] = p;
  size[u] = 1;
  depth[u] = depth[p] + 1;

  for (int i = head[u], v; ~i; i = nx[i])
    if ((v = ed[i]) != p) {
      DFS1(v, u);
      tmp[v] = wt[i];
      size[u] += size[v];
      if (size[pref[u]] < size[v]) pref[u] = v;
    }
}

void DFS2(int u, int t) {
  top[u] = t;
  dfn[u] = ++timestamp;
  w[timestamp] = tmp[u];

  if (!pref[u]) return;
  DFS2(pref[u], t);

  for (int i = head[u], v; ~i; i = nx[i])
    if (v = ed[i], (v != fa[u] && v != pref[u]))
      DFS2(v, v);
}

struct SegT {
  struct Node {
    int sum, max, min;
    int inv, len;
  } t[MAX_V << 2], ret;

  void merge(int u) {
    t[u].sum = t[u << 1].sum + t[u << 1 | 1].sum;
    t[u].max = std::max(t[u << 1].max, t[u << 1 | 1].max);
    t[u].min = std::min(t[u << 1].min, t[u << 1 | 1].min);
  }

  Node merge(Node x, Node y) {
    ret.sum = x.sum + y.sum;
    ret.max = std::max(x.max, y.max);
    ret.min = std::min(x.min, y.min);
    return ret;
  }

  void push(int u) {
    if (!t[u].inv) return;
    Node &lc = t[u << 1], &rc = t[u << 1 | 1];
    lc.inv ^= 1, rc.inv ^= 1;
    lc.sum = -lc.sum, rc.sum = -rc.sum;
    lc.max = -lc.max, rc.max = -rc.max;
    lc.min = -lc.min, rc.min = -rc.min;
    std::swap(lc.max, lc.min), std::swap(rc.max, rc.min);
    t[u].inv = 0;
  }

  void build(int u = 1, int nl = 1, int nr = N) {
    t[u].inv = 0, t[u].len = nr - nl + 1;
    if (nl == nr) return t[u].sum = t[u].max = t[u].min = w[nl], void();
    int mid = (nl + nr) >> 1;
    build(u << 1, nl, mid);
    build(u << 1 | 1, mid + 1, nr);
    merge(u);
  }

  void modify(int p, int x, int u = 1, int nl = 1, int nr = N) {
    if (nl == nr) return t[u].sum = t[u].max = t[u].min = x, void();
    push(u);
    int mid = (nl + nr) >> 1;
    if (p <= mid) modify(p, x, u << 1, nl, mid);
    else modify(p, x, u << 1 | 1, mid + 1, nr);
    merge(u);
  }

  void invert(int l, int r, int u = 1, int nl = 1, int nr = N) {
    if (nl >= l && nr <= r) {
      t[u].inv ^= 1;
      t[u].sum = -t[u].sum;
      t[u].max = -t[u].max;
      t[u].min = -t[u].min;
      return std::swap(t[u].max, t[u].min);
    }
    push(u);
    int mid = (nl + nr) >> 1;
    if (l <= mid) invert(l, r, u << 1, nl, mid);
    if (r > mid) invert(l, r, u << 1 | 1, mid + 1, nr);
    merge(u);
  }

  Node query(int l, int r, int u = 1, int nl = 1, int nr = N) {
    if (nl >= l && nr <= r) return t[u];
    push(u);
    int mid = (nl + nr) >> 1;
    if (l > mid) return query(l, r, u << 1 | 1, mid + 1, nr);
    if (r <= mid) return query(l, r, u << 1, nl, mid);
    return merge(query(l, r, u << 1, nl, mid), query(l, r, u << 1 | 1, mid + 1, nr));
  }
} SEGT;

void modify_edge_val(int i, int w) {
  int x = (i - 1) * 2, y = x + 1;
  int u = (depth[ed[x]] < depth[ed[y]]) ? ed[y] : ed[x];
  SEGT.modify(dfn[u], w);
}

void invert_path_val(int u, int v) {
  while (top[u] != top[v]) {
    if (depth[top[u]] < depth[top[v]]) std::swap(u, v);
    SEGT.invert(dfn[top[u]], dfn[u]);
    u = fa[top[u]];
  }
  if (depth[u] > depth[v]) std::swap(u, v);
  if (u != v) SEGT.invert(dfn[u] + 1, dfn[v]);
}

TUP query_path_attr(int u, int v) {
  int sum = 0, max = -INF, min = INF;
  while (top[u] != top[v]) {
    if (depth[top[u]] < depth[top[v]]) std::swap(u, v);
    SegT::Node ret = SEGT.query(dfn[top[u]], dfn[u]);
    sum += ret.sum, max = std::max(max, ret.max), min = std::min(min, ret.min);
    u = fa[top[u]];
  }
  if (depth[u] > depth[v]) std::swap(u, v);
  if (u != v) {
    SegT::Node ret = SEGT.query(dfn[u] + 1, dfn[v]);
    sum += ret.sum, max = std::max(max, ret.max), min = std::min(min, ret.min);
  }
  return TUP(sum, max, min);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  memset(head, -1, sizeof(int) * (N + 1));

  for (int i = 1, u, v, w; i < N; ++i) {
    std::cin >> u >> v >> w;
    connect(u + 1, v + 1, w);
    connect(v + 1, u + 1, w);
  }

  DFS1(1, 0), DFS2(1, 1);
  SEGT.build();

  int Q;
  std::cin >> Q;

  while (Q--) {
    std::string type;
    int a, b;

    std::cin >> type >> a >> b;

    if (type == "C") modify_edge_val(a, b);
    else if (type == "N") invert_path_val(a + 1, b + 1);
    else {
      auto [x, y, z] = query_path_attr(a + 1, b + 1);
      if (type == "SUM") std::cout << x << '\n';
      else if (type == "MAX") std::cout << y << '\n';
      else std::cout << z << '\n';
    }
  }

  return fflush(stdout), 0;
}
