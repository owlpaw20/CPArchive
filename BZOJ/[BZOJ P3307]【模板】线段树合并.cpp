#include <bits/stdc++.h>

const int MAX_N = 1e5 + 5;
const int MAX_V = 1e5;

int N, q;
std::vector<int> adj[MAX_N];

// ---------- HLD + LCA ----------

int fa[MAX_N], size[MAX_N], depth[MAX_N], pref[MAX_N], top[MAX_N];

void DFS1(int u) {
  size[u] = 1;
  depth[u] = depth[fa[u]] + 1;
  for (int v : adj[u])
    if (v != fa[u]) {
      fa[v] = u, DFS1(v), size[u] += size[v];
      if (!pref[u] || size[pref[u]] < size[v]) pref[u] = v;
    }
}

void DFS2(int u, int t) {
  top[u] = t;
  if (!pref[u]) return;
  DFS2(pref[u], t);
  for (int v : adj[u])
    if (v != pref[u] && v != fa[u]) DFS2(v, v);
}

int LCA(int u, int v) {
  while (top[u] != top[v]) depth[top[u]] < depth[top[v]] ? v = fa[top[v]] : u = fa[top[u]];
  return depth[u] > depth[v] ? v : u;
}

// ---------- Segment Tree ----------

struct SegT {
  struct Node {
    int lc, rc;
    int type, sum;
  } tr[MAX_N << 6];

  int size;

  void pull(int u, int L, int R) {
    if (tr[L].sum < tr[R].sum) tr[u].type = tr[R].type, tr[u].sum = tr[R].sum;
    else tr[u].type = tr[L].type, tr[u].sum = tr[L].sum;
  }

  void upd(int x, int val, int& u, int nl = 1, int nr = MAX_V) {
    if (!u) u = ++size;
    if (nl == nr) return tr[u].type = x, tr[u].sum += val, void();
    int mid = (nl + nr) >> 1;
    if (x <= mid) upd(x, val, tr[u].lc, nl, mid);
    else upd(x, val, tr[u].rc, mid + 1, nr);
    pull(u, tr[u].lc, tr[u].rc);
  }

  void join(int& u, int v, int nl = 1, int nr = MAX_V) {
    if (!v) return;
    if (!u) return u = v, void();
    if (nl == nr) return tr[u].sum += tr[v].sum, void();
    int mid = (nl + nr) >> 1;
    join(tr[u].lc, tr[v].lc, nl, mid);
    join(tr[u].rc, tr[v].rc, mid + 1, nr);
    pull(u, tr[u].lc, tr[u].rc);
  }
} T;

int rt[MAX_N];

// ---------- Get Answer ----------

int ans[MAX_N];

void DFS(int u) {
  for (int v : adj[u])
    if (v != fa[u])
      DFS(v), T.join(rt[u], rt[v]);
  ans[u] = T.tr[rt[u]].sum ? T.tr[rt[u]].type : 0;
}

// --------- Main Function -----------

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> q;

  for (int i = 1, u, v; i < N; ++i) {
    std::cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  DFS1(1), DFS2(1, 1);

  while (q--) {
    static int x, y, z, lca;
    std::cin >> x >> y >> z, lca = LCA(x, y);

    T.upd(z, 1, rt[x]);
    T.upd(z, 1, rt[y]);
    T.upd(z, -1, rt[lca]);
    T.upd(z, -1, rt[fa[lca]]);
  }

  DFS(1);

  for (int i = 1; i <= N; ++i) std::cout << ans[i] << '\n';
  std::cout.flush();
  return 0;
}
