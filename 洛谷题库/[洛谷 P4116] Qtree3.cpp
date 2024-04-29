#include <vector>
#include <cstring>
#include <iostream>

#define endl '\n'

namespace FastIO {
  const int MAX_BUF = 1 << 16;
  char buf[MAX_BUF], *p1, *p2;
  char pbuf[MAX_BUF], *pp = pbuf;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAX_BUF, stdin), p1 == p2) ? EOF : *p1++)
#define putchar(c) (((pp - pbuf == MAX_BUF) && (fwrite(pbuf, 1, MAX_BUF, stdout), pp = pbuf)), *pp++ = c)
#define flush() ((pp - pbuf) && fwrite(pbuf, 1, pp - pbuf, stdout))

  template <typename T>
  inline T read() {
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
  inline void write(T x) {
    static int stack[40];
    int top = 0;
    do stack[top++] = x % 10, x /= 10;
    while (x);
    while (top) putchar(stack[--top] + 48);
  }
}  // namespace FastIO
using namespace FastIO;

const int MAX_V = 1e5 + 5;
const int MAX_E = 2e5 + 5;
const int INF = 0x3F3F3F3F;

int N;
int ed[MAX_E], nx[MAX_E], head[MAX_V], idx;

inline void connect(const int u, const int v) {
  ed[idx] = v;
  nx[idx] = head[u];
  head[u] = idx++;
}

namespace HLD {
  int par[MAX_V], size[MAX_V], dept[MAX_V], hv[MAX_V];
  int dfn[MAX_V], top[MAX_V], mir[MAX_V], ts;

  void DFS1(int u, int p) {
    par[u] = p;
    size[u] = 1;
    dept[u] = dept[p] + 1;

    for (int i = head[u], v; ~i; i = nx[i]) {
      if ((v = ed[i]) == p) continue;
      DFS1(v, u);
      size[u] += size[v];
      if (!hv[u] || size[hv[u]] < size[v]) hv[u] = v;
    }
  }

  void DFS2(int u, int t) {
    top[u] = t;
    dfn[u] = ++ts;
    mir[ts] = u;

    if (!hv[u]) return;
    DFS2(hv[u], t);

    for (int i = head[u], v; ~i; i = nx[i])
      if (v = ed[i], (v != par[u] && v != hv[u]))
        DFS2(v, v);
  }

  int query_on_path(int, int);
}  // namespace HLD
using namespace HLD;

struct SegT {
  bool c[MAX_V << 2];
  int fb[MAX_V << 2];

  void init() { memset(fb, 0x3F, sizeof(int) * (N * 4 + 1)); }
  void pull(int u) { fb[u] = std::min(fb[u << 1], fb[u << 1 | 1]); }

  void invert(int x, int u = 1, int nl = 1, int nr = N) {
    if (nl == nr) return c[u] ^= 1, fb[u] = (c[u] ? nl : INF), void();
    int mid = (nl + nr) >> 1;
    if (x <= mid) invert(x, u << 1, nl, mid);
    else invert(x, u << 1 | 1, mid + 1, nr);
    pull(u);
  }

  int query(int l, int r, int u = 1, int nl = 1, int nr = N) {
    if (nl >= l && nr <= r) return fb[u];
    int mid = (nl + nr) >> 1, ret = INF;
    if (l <= mid) ret = std::min(ret, query(l, r, u << 1, nl, mid));
    if (r > mid) ret = std::min(ret, query(l, r, u << 1 | 1, mid + 1, nr));
    return ret;
  }

} SEGT;

int HLD::query_on_path(int u, int v) {
  int ret = INF;
  while (top[u] != top[v]) {
    if (dept[u] > dept[v]) std::swap(u, v);
    ret = std::min(ret, SEGT.query(dfn[top[v]], dfn[v]));
    v = par[top[v]];
  }

  if (dept[u] < dept[v]) std::swap(u, v);
  ret = std::min(ret, SEGT.query(dfn[v], dfn[u]));
  return ret == INF ? -1 : mir[ret];
}

int main() {
  N = read<int>();
  int Q = read<int>();

  memset(head, -1, sizeof(int) * (N + 1));
  SEGT.init();

  for (int i = 1, u, v; i < N; ++i) {
    u = read<int>(), v = read<int>();
    connect(u, v);
    connect(v, u);
  }

  DFS1(1, 0);
  DFS2(1, 1);

  while (Q--) {
    int type = read<int>();
    int u = read<int>();

    if (type) std::cout << query_on_path(1, u) << endl;
    else SEGT.invert(dfn[u]);
  }

  flush(), fflush(stdout);
  return 0;
}
