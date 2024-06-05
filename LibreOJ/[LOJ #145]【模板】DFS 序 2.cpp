#include <cstring>
#include <iostream>

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
    if (x < 0) putchar('-'), x = -x;
    int top = 0;
    do stack[top++] = x % 10, x /= 10;
    while (x);
    while (top) putchar(stack[--top] + 48);
  }
}  // namespace FastIO
using namespace FastIO;

using l64 = long long;

const int MAX_V = 1e6 + 5;
const int MAX_E = 2e6 + 5;

int N, M, R, w[MAX_V], _w[MAX_V];
int ed[MAX_E], nx[MAX_E], head[MAX_V], idx;
int dfn[MAX_V], size[MAX_V], timestamp;

void connect(int u, int v) {
  ed[idx] = v;
  nx[idx] = head[u];
  head[u] = idx++;
}

void DFS(int u) {
  size[u] = 1;
  dfn[u] = ++timestamp;
  _w[timestamp] = w[u];

  for (int i = head[u], v; ~i; i = nx[i])
    if (!dfn[v = ed[i]])
      DFS(v), size[u] += size[v];
}

struct SegT {
  l64 sum[MAX_V << 2], tag[MAX_V << 2];
  int len[MAX_V << 2];

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
    if (nl == nr) return sum[u] = _w[nl], void();
    int mid = (nl + nr) >> 1;
    build(u << 1, nl, mid), build(u << 1 | 1, mid + 1, nr);
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

int main() {
  N = read<int>(), M = read<int>(), R = read<int>();
  for (int i = 1; i <= N; ++i) w[i] = read<int>();
  memset(head, -1, sizeof(int) * (N + 1));

  for (int i = 1, u, v; i < N; ++i) {
    u = read<int>(), v = read<int>();
    connect(u, v);
    connect(v, u);
  }

  DFS(R);

  SEGT.build();

  while (M--) {
    int type = read<int>(), a = read<int>();
    if (type == 1) SEGT.update(dfn[a], dfn[a] + size[a] - 1, read<int>());
    else write(SEGT.query(dfn[a], dfn[a] + size[a] - 1)), putchar('\n');
  }

  return flush(), fflush(stdout), 0;
}
