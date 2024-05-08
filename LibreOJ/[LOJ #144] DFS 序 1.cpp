#include <cstring>
#include <numeric>
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

struct Fenwick {
  l64 c[MAX_V];

  void update(int x, int d) {
    for (; x <= N; x += (x & -x))
      c[x] += d;
  }

  l64 query(int x) {
    l64 sum = 0;
    for (; x; x -= (x & -x)) sum += c[x];
    return sum;
  }
} fen;

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

  std::inclusive_scan(_w + 1, _w + timestamp + 1, _w + 1, std::plus(), 0LL);
  for (int i = 1; i <= timestamp; ++i) fen.c[i] = _w[i] - _w[i - (i & -i)];

  while (M--) {
    int type = read<int>();

    if (type == 1) {
      int a = read<int>(), x = read<int>();
      fen.update(dfn[a], x);
    } else {
      int x = read<int>();
      write(fen.query(dfn[x] + size[x] - 1) - fen.query(dfn[x] - 1)), putchar('\n');
    }
  }

  return flush(), fflush(stdout), 0;
}
