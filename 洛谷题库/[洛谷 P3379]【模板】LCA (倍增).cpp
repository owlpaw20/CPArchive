#include <queue>
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
    if (x < 0) putchar('-'), x = -x;
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

int N, M, R, logN;

int ed[MAX_E], nx[MAX_E], head[MAX_V], idx;
int depth[MAX_V], anc[20][MAX_V];

void connect(int u, int v) {
  ed[idx] = v;
  nx[idx] = head[u];
  head[u] = idx++;
}

void prep() {
  std::queue<int> q;

  q.push(R);
  depth[R] = 1;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int i = head[u], v; ~i; i = nx[i]) {
      if (depth[v = ed[i]]) continue;

      anc[0][v] = u;
      depth[v] = depth[u] + 1;
      for (int i = 1; i < logN; ++i)
        anc[i][v] = anc[i - 1][anc[i - 1][v]];

      q.push(v);
    }
  }
}

int get_LCA(int u, int v) {
  if (depth[u] > depth[v]) std::swap(u, v);

  for (int i = logN - 1; ~i; --i)
    if (depth[v] - depth[u] >= (1 << i))
      v = anc[i][v];

  if (u == v) return u;

  for (int i = logN - 1; ~i; --i)
    if (anc[i][u] != anc[i][v])
      u = anc[i][u], v = anc[i][v];

  return anc[0][u];
}

int main() {
  N = read<int>(), logN = std::max(20, std::__lg(N) + 1);
  M = read<int>();
  R = read<int>();

  memset(head, -1, sizeof(int) * (N + 1));

  for (int i = 1, u, v; i < N; ++i) {
    u = read<int>(), v = read<int>();
    connect(u, v);
    connect(v, u);
  }

  prep();

  while (M--) {
    int u = read<int>();
    int v = read<int>();
    write(get_LCA(u, v)), putchar('\n');
  }

  flush(), fflush(stdout);
  return 0;
}
