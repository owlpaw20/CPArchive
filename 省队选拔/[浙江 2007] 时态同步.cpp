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
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - 48, ch = getchar();
    return x * f;
  }

  template <typename T>
  void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
  }
}  // namespace FastIO
using namespace FastIO;

using i64 = long long int;

const int MAX_N = 5e5 + 5;
const int MAX_M = 1e6 + 5;

int n, s;
int ed[MAX_M], nx[MAX_M], wt[MAX_M];
int head[MAX_N], idx;
i64 max_dist[MAX_N], ans;

inline void connect(const int u, const int v, const int w) {
  ed[idx] = v;
  wt[idx] = w;
  nx[idx] = head[u];
  head[u] = idx++;
}

void DFS(const int u, const int fa) {
  for (int i = head[u]; ~i; i = nx[i]) {
    int v = ed[i], w = wt[i];
    if (v == fa) continue;
    DFS(v, u);
    max_dist[u] = std::max(max_dist[u], max_dist[v] + w);
  }

  for (int i = head[u]; ~i; i = nx[i]) {
    int v = ed[i], w = wt[i];
    if (v == fa) continue;
    ans += max_dist[u] - max_dist[v] - w;
  }
}

int main() {
  n = read<int>(), s = read<int>();

  std::fill(head, head + n + 1, -1);

  for (int i = 1, u, v, w; i < n; ++i) {
    u = read<int>(), v = read<int>(), w = read<int>();
    connect(u, v, w), connect(v, u, w);
  }

  DFS(s, -1);

  std::cout << ans << endl;
  return fflush(stdout), 0;
}
