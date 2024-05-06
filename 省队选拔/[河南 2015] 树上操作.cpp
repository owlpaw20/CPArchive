#include <vector>
#include <iostream>

#define endl '\n'

using l64 = long long;

const int MAX_V = 1e5 + 5;

std::vector<int> adj[MAX_V];

int N, M;
int val[MAX_V], _val[MAX_V];

struct SegT {
  int len[MAX_V << 2];
  l64 sum[MAX_V << 2], tag[MAX_V << 2];

  void merge(int u) { sum[u] = sum[u << 1] + sum[u << 1 | 1]; }

  void push(int u) {
    if (!tag[u]) return;
    tag[u << 1] += tag[u];
    sum[u << 1] += tag[u] * len[u << 1];
    tag[u << 1 | 1] += tag[u];
    sum[u << 1 | 1] += tag[u] * len[u << 1 | 1];
    tag[u] = 0;
  }

  void build(int u = 1, int nl = 1, int nr = N) {
    tag[u] = 0, len[u] = nr - nl + 1;
    if (nl == nr) return sum[u] = _val[nl], void();
    int mid = (nl + nr) >> 1;
    build(u << 1, nl, mid);
    build(u << 1 | 1, mid + 1, nr);
    merge(u);
  }

  void update(int l, int r, l64 x, int u = 1, int nl = 1, int nr = N) {
    if (nl >= l && nr <= r) {
      tag[u] += x;
      sum[u] += x * len[u];
      return;
    }
    push(u);
    int mid = (nl + nr) >> 1;
    if (l <= mid) update(l, r, x, u << 1, nl, mid);
    if (r > mid) update(l, r, x, u << 1 | 1, mid + 1, nr);
    merge(u);
  }

  l64 query(int l, int r, int u = 1, int nl = 1, int nr = N) {
    if (nl >= l && nr <= r) return sum[u];
    push(u);
    int mid = (nl + nr) >> 1;
    l64 sum = 0;
    if (l <= mid) sum += query(l, r, u << 1, nl, mid);
    if (r > mid) sum += query(l, r, u << 1 | 1, mid + 1, nr);
    return sum;
  }
  
} SEGT;

int size[MAX_V], pref[MAX_V], depth[MAX_V], fa[MAX_V];
int top[MAX_V], dfn[MAX_V], ts;

void DFS1(int u, int p) {
  fa[u] = p;
  size[u] = 1;
  depth[u] = depth[p] + 1;

  for (int v : adj[u])
    if (v != p) {
      DFS1(v, u);
      size[u] += size[v];
      if (size[pref[u]] < size[v]) pref[u] = v;
    }
}

void DFS2(int u, int t) {
  top[u] = t;
  dfn[u] = ++ts;
  _val[ts] = val[u];

  if (!pref[u]) return;
  DFS2(pref[u], t);

  for (int v : adj[u])
    if (v != fa[u] && v != pref[u])
      DFS2(v, v);
}

void update_vertex(int u, l64 x) { SEGT.update(dfn[u], dfn[u], x); }
void update_subtree(int u, l64 x) { SEGT.update(dfn[u], dfn[u] + size[u] - 1, x); }

l64 query_path_sum(int u) {
  l64 sum = 0;
  while (top[u] != 1) {
    sum += SEGT.query(dfn[top[u]], dfn[u]);
    u = fa[top[u]];
  }
  sum += SEGT.query(1, dfn[u]);
  return sum;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;
  for (int i = 1; i <= N; ++i) std::cin >> val[i];

  for (int i = 1, u, v; i < N; ++i) {
    std::cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  DFS1(1, 0), DFS2(1, 1);
  SEGT.build();

  while (M--) {
    int type, x;
    std::cin >> type >> x;

    if (type == 3)
      std::cout << query_path_sum(x) << endl;
    else {
      int a;
      std::cin >> a;
      if (type == 1) update_vertex(x, a);
      else update_subtree(x, a);
    }
  }

  fflush(stdout);
  return 0;
}
