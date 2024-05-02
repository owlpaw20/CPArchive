// 写法出自 https://www.luogu.com.cn/article/pu52m9ue

#pragma pack(1)

#include <cstring>
#include <iostream>

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
int dfn[MAX_V], ts;

void connect(int u, int v) {
  ed[idx] = v;
  nx[idx] = head[u];
  head[u] = idx++;
}

struct SparseTable {
  int min[20][MAX_V];

  void init() {
    int lmt = std::max(20, std::__lg(ts) + 1);
    for (int i = 1; i < lmt; ++i)
      for (int j = 1, x, y; j + (1 << i) - 1 <= ts; ++j)
        min[i][j] = dfn[x = min[i - 1][j]] < dfn[y = min[i - 1][j + (1 << (i - 1))]] ? x : y;
  }

  int query(int l, int r) {
    if (l > r) std::swap(l, r);
    int t = std::__lg(r - l), x, y;
    return dfn[x = min[t][l + 1]] < dfn[y = min[t][r - (1 << t) + 1]] ? x : y;
  }
} ST;

void DFS(int u, int p) {
  ST.min[0][dfn[u] = ++ts] = p;
  for (int i = head[u]; ~i; i = nx[i])
    if (ed[i] != p)
      DFS(ed[i], u);
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

  DFS(R, 0);
  ST.init();

  while (M--) {
    int u = read<int>(), v = read<int>();
    write(u == v ? u : ST.query(dfn[u], dfn[v])), putchar('\n');
  }

  flush(), fflush(stdout);
  return 0;
}
