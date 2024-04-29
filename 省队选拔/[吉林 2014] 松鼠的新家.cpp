#include <cstring>
#include <iostream>
#include <algorithm>

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

const int MAX_V = 3e5 + 5;
const int MAX_E = 6e5 + 5;

int N;
int ed[MAX_E], nx[MAX_E], head[MAX_V], idx;
int d[MAX_V], a[MAX_V];

inline void connect(const int u, const int v) {
  ed[idx] = v;
  nx[idx] = head[u];
  head[u] = idx++;
}

namespace HLD {
  int fa[MAX_V], size[MAX_V], pref[MAX_V], depth[MAX_V];
  int top[MAX_V];

  void DFS1(int u, int p) {
    fa[u] = p;
    size[u] = 1;
    depth[u] = depth[p] + 1;

    for (int i = head[u], v; ~i; i = nx[i]) {
      if ((v = ed[i]) == p) continue;
      DFS1(v, u);
      size[u] += size[v];
      if (size[pref[u]] < size[v]) pref[u] = v;
    }
  }

  void DFS2(int u, int t) {
    top[u] = t;

    if (!pref[u]) return;
    DFS2(pref[u], t);

    for (int i = head[u], v; ~i; i = nx[i])
      if (v = ed[i], (v != fa[u] && v != pref[u]))
        DFS2(v, v);
  }

  int query_LCA(int u, int v) {
    while (top[u] != top[v])
      if (depth[top[u]] < depth[top[v]]) v = fa[top[v]];
      else u = fa[top[u]];
    return depth[u] > depth[v] ? v : u;
  }
}  // namespace HLD
using namespace HLD;

void calc(int u) {
  for (int i = head[u], v; ~i; i = nx[i]) {
    if ((v = ed[i]) == fa[u]) continue;
    calc(v);
    d[u] += d[v];
  }
}

int main() {
  N = read<int>();
  memset(head, -1, sizeof(int) * (N + 1));
  for (int i = 1; i <= N; ++i) a[i] = read<int>();

  for (int i = 1, u, v; i < N; ++i) {
    u = read<int>(), v = read<int>();
    connect(u, v);
    connect(v, u);
  }

  DFS1(1, 0);
  DFS2(1, 1);

  for (int i = 2; i <= N; ++i) {
    int LCA = query_LCA(a[i - 1], a[i]);
    ++d[a[i - 1]], ++d[a[i]], --d[LCA], --d[fa[LCA]];
  }

  calc(1);
  for (int i = 2; i <= N; ++i) --d[a[i]];
  for (int i = 1; i <= N; ++i) write(d[i]), putchar('\n');

  flush(), fflush(stdout);
  return 0;
}
