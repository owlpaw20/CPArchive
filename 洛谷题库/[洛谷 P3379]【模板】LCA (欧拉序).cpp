#include <bits/stdc++.h>

#define endl '\n'

namespace FastIO {
  const int MAX_BUF = 1 << 20;
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

  inline std::string sread() {
    std::string var;
    char ch = getchar();
    while (iswspace(ch)) ch = getchar();
    while (!iswspace(ch)) var.push_back(ch), ch = getchar();
    return var;
  }

  inline void swrite(const std::string s) {
    for (char ch : s)
      putchar(ch);
  }
}  // namespace FastIO
using namespace FastIO;

const int MAX_V = 5e5 + 5;
const int MAX_E = 1e6 + 5;

int N, M, R;
int ed[MAX_E], nx[MAX_E], head[MAX_V], idx;
int dfn[MAX_V], ver[MAX_E], depth[MAX_E], ts;

void connect(int u, int v) {
  ed[idx] = v;
  nx[idx] = head[u];
  head[u] = idx++;
}

struct SparseTable {
  int f[21][MAX_E];
  int min[21][MAX_E];

  void init() {
    int lmt = std::min(21, std::__lg(ts) + 1);
    for (int i = 1; i <= ts; ++i)
      f[0][i] = depth[i], min[0][i] = ver[i];
    for (int i = 1; i < lmt; ++i)
      for (int j = 1; j + (1 << i) - 1 <= ts; ++j) {
        bool t = f[i - 1][j] < f[i - 1][j + (1 << (i - 1))];
        f[i][j] = t ? f[i - 1][j] : f[i - 1][j + (1 << (i - 1))];
        min[i][j] = t ? min[i - 1][j] : min[i - 1][j + (1 << (i - 1))];
      }
  }

  int query(int l, int r) {
    if (l > r) std::swap(l, r);
    int t = std::__lg(r - l + 1);
    return f[t][l] < f[t][r - (1 << t) + 1] ? min[t][l] : min[t][r - (1 << t) + 1];
  }
} ST;

void DFS(int u, int d) {
  dfn[u] = ++ts;
  ver[ts] = u;
  depth[ts] = d;

  for (int i = head[u]; ~i; i = nx[i])
    if (!dfn[ed[i]])
      DFS(ed[i], d + 1), ver[++ts] = u, depth[ts] = d;
}

int main() {
  N = read<int>();
  M = read<int>();
  R = read<int>();

  memset(head, -1, sizeof(int) * (N + 1));

  for (int i = 1, u, v; i < N; ++i) {
    u = read<int>(), v = read<int>();
    connect(u, v);
    connect(v, u);
  }

  DFS(R, 1);
  ST.init();

  while (M--) {
    int u = read<int>(), v = read<int>();
    write(ST.query(dfn[u], dfn[v])), putchar('\n');
  }

  flush(), fflush(stdout);
  return 0;
}
