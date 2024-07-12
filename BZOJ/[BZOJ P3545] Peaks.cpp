#include <vector>
#include <cstring>
#include <numeric>
#include <iostream>
#include <algorithm>

namespace FastIO {
  const int MAX_BUF = 1 << 20;
  char buf[MAX_BUF], *p1, *p2;
  char pbuf[MAX_BUF], *pp = pbuf;

  char getchar() { return (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAX_BUF, stdin), p1 == p2) ? EOF : *p1++); }
  void putchar(char c) { (((pp - pbuf == MAX_BUF) && (fwrite(pbuf, 1, MAX_BUF, stdout), pp = pbuf)), *pp++ = c); }
  void flush() { (pp - pbuf) && fwrite(pbuf, 1, pp - pbuf, stdout); }

  template <typename T = int>
  T read() {
    short int f = 1;
    T var = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
      if (ch == '-') f = -f;
      ch = getchar();
    }
    while (ch >= '0' && ch <= '9') var = var * 10 + ch - '0', ch = getchar();
    return var * f;
  }

  template <typename T>
  void write(T x) {
    static int stack[40];
    if (x < 0) putchar('-'), x = -x;
    int top = 0;
    do stack[top++] = x % 10, x /= 10;
    while (x);
    while (top) putchar(stack[--top] + 48);
  }
}  // namespace FastIO
using namespace FastIO;

const int MAX_N = 2e5 + 5;
const int MAX_M = 1e6 + 5;

int N, M;
int h[MAX_N], t[MAX_N];

std::vector<int> adj[MAX_N];

struct Edge {
  int u, v, w;
} edge[MAX_M];

int fa[MAX_N], ver_w[MAX_N], cnt;
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

void Kruskal() {
  auto cmp = [](const Edge &x, const Edge &y) { return x.w < y.w; };
  std::sort(edge + 1, edge + M + 1, cmp);

  std::iota(fa, fa + N * 2 + 1, 0);
  memset(ver_w, 0, sizeof(int) * (N * 2 + 1));

  cnt = N;
  for (int i = 1; i <= M; ++i) {
    int fu = find(edge[i].u), fv = find(edge[i].v);
    if (fu == fv) continue;
    fa[fu] = fa[fv] = ++cnt;
    ver_w[cnt] = edge[i].w;
    adj[cnt].push_back(fu), adj[cnt].push_back(fv);
    if (cnt == N * 2 - 1) break;
  }
}

struct PerSegT {
  struct Node {
    int l, r;
    int cnt;
  } tr[MAX_N << 5];

  int size;

  int upd(int x, int u, int nl = 1, int nr = N * 2) {
    int v = ++size;
    tr[v] = tr[u];
    if (nl == nr) return ++tr[v].cnt, v;
    int mid = (nl + nr) >> 1;
    if (x <= mid) tr[v].l = upd(x, tr[u].l, nl, mid);
    else tr[v].r = upd(x, tr[u].r, mid + 1, nr);
    tr[v].cnt = tr[tr[v].l].cnt + tr[tr[v].r].cnt;
    return v;
  }

  int qry(int u, int v, int k, int nl = 1, int nr = N * 2) {
    if (nl == nr) return nl;
    int mid = (nl + nr) >> 1, cnt = tr[tr[v].r].cnt - tr[tr[u].r].cnt;
    if (k <= cnt) return qry(tr[u].r, tr[v].r, k, mid + 1, nr);
    else return qry(tr[u].l, tr[v].l, k - cnt, nl, mid);
  }

  PerSegT() : size(0) {}
} PST;

int root[MAX_N];
int f[MAX_N][20], depth[MAX_N];
int st[MAX_N], fn[MAX_N], idx;
int leaf_cnt[MAX_N];

void DFS(int u, int p) {
  f[u][0] = p;
  for (int i = 1; i < 20; ++i) f[u][i] = f[f[u][i - 1]][i - 1];

  st[u] = ++idx;
  leaf_cnt[u] = adj[u].empty();

  if (u <= N) root[idx] = PST.upd(h[u], root[idx - 1]);
  else root[idx] = root[idx - 1];

  for (int v : adj[u]) DFS(v, u), leaf_cnt[u] += leaf_cnt[v];
  fn[u] = idx;
}

int main() {
  N = read(), M = read();
  int q = read();

  for (int i = 1; i <= N; ++i) t[i] = h[i] = read();
  for (int i = 1; i <= M; ++i) edge[i] = (Edge){read(), read(), read()};

  std::sort(t + 1, t + N + 1);
  int shift = std::unique(t + 1, t + N + 1) - t - 1;
  for (int i = 1; i <= N; ++i)
    h[i] = std::lower_bound(t + 1, t + shift + 1, h[i]) - t;

  Kruskal();

  DFS(cnt, 0);

  while (q--) {
    static int v, x, k;
    v = read(), x = read(), k = read();

    for (int i = 19; ~i; --i)
      if (f[v][i] && ver_w[f[v][i]] <= x)
        v = f[v][i];

    if (leaf_cnt[v] < k) {
      write(-1), putchar('\n');
      continue;
    }

    int qu = root[fn[v]], qv = root[st[v] - 1];
    write(t[PST.qry(qv, qu, k)]), putchar('\n');
  }

  return flush(), 0;
}
