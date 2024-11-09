#include <bits/stdc++.h>

namespace FastIO {
  const int MAX_BUF = 1 << 16;
  char buf[MAX_BUF], *p1, *p2;
  char pbuf[MAX_BUF], *pp = pbuf;

  char getchar() { return (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAX_BUF, stdin), p1 == p2) ? EOF : *p1++); }
  void putchar(char c) { (((pp - pbuf == MAX_BUF) && (fwrite(pbuf, 1, MAX_BUF, stdout), pp = pbuf)), *pp++ = c); }
  void flush() { (pp - pbuf) && fwrite(pbuf, 1, pp - pbuf, stdout); }

  int read() {
    short int f = 1;
    int var = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
      if (ch == '-') f = -f;
      ch = getchar();
    }
    while (ch >= '0' && ch <= '9') var = var * 10 + ch - '0', ch = getchar();
    return var * f;
  }

  void write(int x) {
    static short int stack[20];
    if (x < 0) putchar('-'), x = -x;
    int top = 0;
    do stack[top++] = x % 10, x /= 10;
    while (x);
    while (top) putchar(stack[--top] + 48);
  }
}  // namespace FastIO
using namespace FastIO;

const int MAX_N = 1e5 + 5;

int N, M, pool;
std::vector<std::vector<int>> g;

int fa[MAX_N], size[MAX_N], pref[MAX_N], dep[MAX_N];
int top[MAX_N], dfn[MAX_N], ts;

void DFS1(int u, int f) {
  fa[u] = f;
  size[u] = 1;
  dep[u] = dep[f] + 1;

  for (int v : g[u]) {
    if (v == f) continue;
    DFS1(v, u);
    size[u] += size[v];
    if (size[v] >= size[pref[u]]) pref[u] = v;
  }
}

void DFS2(int u, int p) {
  top[u] = p;
  dfn[u] = ++ts;

  if (!pref[u]) return;
  DFS2(pref[u], p);

  for (int v : g[u])
    if (v != fa[u] && v != pref[u])
      DFS2(v, v);
}

struct SegT {
  struct Node {
    int ans, lval, rval, tag, len;
    void inherit_tag(int _tag) { ans = len - 1, lval = rval = tag = _tag; }
  } tr[MAX_N << 2];

  Node merge(const Node& L, const Node& R) {
    int ans = L.ans + R.ans + (L.rval == R.lval);
    return (Node){ans, L.lval, R.rval, 0, L.len + R.len};
  }

  void push_tag(int u) {
    if (!tr[u].tag) return;
    tr[u << 1].inherit_tag(tr[u].tag);
    tr[u << 1 | 1].inherit_tag(tr[u].tag);
    tr[u].tag = 0;
  }

  void build(int u = 1, int nl = 1, int nr = N) {
    tr[u].tag = 0, tr[u].len = nr - nl + 1;
    if (nl == nr) return tr[u].ans = 0, tr[u].lval = tr[u].rval = ++pool, void();
    int mid = (nl + nr) >> 1;
    build(u << 1, nl, mid);
    build(u << 1 | 1, mid + 1, nr);
    tr[u] = merge(tr[u << 1], tr[u << 1 | 1]);
  }

  void upd(int l, int r, int v, int u = 1, int nl = 1, int nr = N) {
    if (nl >= l && nr <= r) return tr[u].inherit_tag(v);
    push_tag(u);
    int mid = (nl + nr) >> 1;
    if (l <= mid) upd(l, r, v, u << 1, nl, mid);
    if (r > mid) upd(l, r, v, u << 1 | 1, mid + 1, nr);
    tr[u] = merge(tr[u << 1], tr[u << 1 | 1]);
  }

  Node qry(int l, int r, int u = 1, int nl = 1, int nr = N) {
    if (nl >= l && nr <= r) return tr[u];
    push_tag(u);
    int mid = (nl + nr) >> 1;
    if (r <= mid) return qry(l, r, u << 1, nl, mid);
    if (l > mid) return qry(l, r, u << 1 | 1, mid + 1, nr);
    return merge(qry(l, r, u << 1, nl, mid), qry(l, r, u << 1 | 1, mid + 1, nr));
  }

  Node qry(int x) { return qry(x, x); }
} T;

void upd_path(int u, int v, int x) {
  while (top[u] != top[v]) {
    if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
    T.upd(dfn[top[u]], dfn[u], x);
    u = fa[top[u]];
  }
  if (dep[u] > dep[v]) std::swap(u, v);
  T.upd(dfn[u], dfn[v], x);
}

int qry_path(int u, int v) {
  int ans = 0;
  while (top[u] != top[v]) {
    if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
    ans += T.qry(dfn[top[u]], dfn[u]).ans;
    ans += T.qry(dfn[fa[top[u]]]).lval == T.qry(dfn[top[u]]).lval;
    u = fa[top[u]];
  }
  if (dep[u] > dep[v]) std::swap(u, v);
  return ans + T.qry(dfn[u], dfn[v]).ans;
}

void solve() {
  N = read(), M = read();
  g = std::vector<std::vector<int>>(N + 1);

  pool = ts = 0;
  memset(pref, 0, sizeof(int) * (N + 1));
  memset(T.tr, 0, sizeof(SegT::Node) * ((N + 1) << 2));

  for (int i = 1, u, v; i < N; ++i) {
    u = read(), v = read();
    g[u].push_back(v), g[v].push_back(u);
  }

  DFS1(1, 0), DFS2(1, 1);
  T.build();

  while (M--)
    if (read() == 1) upd_path(read(), read(), ++pool);
    else write(qry_path(read(), read())), putchar('\n');
}

int main() {
  int T = read();
  while (T--) solve();
  return flush(), 0;
}
