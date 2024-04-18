#include <cstring>
#include <iostream>

#define endl '\n'

namespace FastIO {
  const int MAX_BUF = 1 << 20;
  char buf[MAX_BUF], *p1, *p2;

#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++)

  template <typename T>
  T read() {
    T x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
      if (ch == '-') f = -f;
      ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
      x = x * 10 + ch - 48, ch = getchar();
    return x * f;
  }
}  // namespace FastIO
using namespace FastIO;

const int MAX_N = 5e4 + 5;
const int MAX_M = 1e5 + 5;

int ed[MAX_M], nx[MAX_M], head[MAX_N], idx;
bool vis[MAX_N], contains_cycle;

inline void connect(const int u, const int v) {
  ed[idx] = v;
  nx[idx] = head[u];
  head[u] = idx++;
}

void DFS(int u, int fa) {
  vis[u] = true;
  for (int i = head[u]; ~i; i = nx[i]) {
    if (ed[i] == fa) continue;
    if (vis[ed[i]]) {
      contains_cycle = true;
      return;
    } else {
      DFS(ed[i], u);
      if (contains_cycle) return;
    }
  }
}

void solve() {
  memset(ed, 0, sizeof ed);
  memset(nx, 0, sizeof nx);
  memset(vis, 0, sizeof vis);
  memset(head, -1, sizeof head);
  idx = 0, contains_cycle = false;

  int m;
  read<int>(), m = read<int>();

  for (int i = 1, u, v; i <= m; ++i) {
    u = read<int>(), v = read<int>();
    connect(u, v), connect(v, u);
  }

  DFS(1, -1);

  puts(contains_cycle ? "0.000" : "1.000");
}

int main() {
  int T = read<int>();
  while (T--) solve();

  fflush(stdout);
  return 0;
}
