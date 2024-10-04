#include <bits/stdc++.h>

namespace FastIO {
  const int MAX_BUF = 1 << 16;
  char buf[MAX_BUF], *p1, *p2;
  char pbuf[MAX_BUF], *pp = pbuf;

  char getchar() { return (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAX_BUF, stdin), p1 == p2) ? EOF : *p1++); }
  void putchar(char c) { (((pp - pbuf == MAX_BUF) && (fwrite(pbuf, 1, MAX_BUF, stdout), pp = pbuf)), *pp++ = c); }
  void flush() { (pp - pbuf) && fwrite(pbuf, 1, pp - pbuf, stdout); }

  template <typename T>
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

using PII = std::pair<int, int>;

const int MAX_N = 3e5 + 5;

int N, M;
std::vector<std::vector<PII>> g;

int fa[MAX_N], dep[MAX_N], dist[MAX_N], size[MAX_N], pref[MAX_N];

void DFS1(int u, int f) {
  fa[u] = f;
  size[u] = 1;
  dep[u] = dep[f] + 1;

  for (auto [v, w] : g[u]) {
    if (v == f) continue;
    dist[v] = dist[u] + w;
    DFS1(v, u);
    size[u] += size[v];
    if (size[pref[u]] < size[v]) pref[u] = v;
  }
}

int top[MAX_N];
int ver[MAX_N], ts;

void DFS2(int u, int t) {
  top[u] = t;
  ver[++ts] = u;

  if (!pref[u]) return;
  DFS2(pref[u], t);

  for (auto [v, w] : g[u])
    if (v != fa[u] && v != pref[u])
      DFS2(v, v);
}

int qry_LCA(int u, int v) {
  while (top[u] != top[v]) dep[top[u]] > dep[top[v]] ? u = fa[top[u]] : v = fa[top[v]];
  return dep[u] > dep[v] ? v : u;
}

struct Plan {
  int u, v, lca, len;
} plans[MAX_N];

bool check(int x) {
  std::vector<int> diff(N + 1);  // 树上差分

  int maxDelta = 0;  // 使所有链长大于 x 的链都减小到 x 以内所需要清零的边的最短长度
  int cnt = 0;       // 原链长大于 x 的链的数量

  for (int i = 1; i <= M; ++i) {
    auto [u, v, lca, len] = plans[i];
    if (len <= x) continue;

    ++cnt;
    maxDelta = std::max(maxDelta, len - x);

    // 这里统计的边是从当前节点连向父节点的边，也就是当前节点的返祖边
    // 所以差分在当前节点减 2 次，累加起来才能表示经过这条边的链的总数
    ++diff[u], ++diff[v], diff[lca] -= 2;
  }

  // 如果所有链长都已经在 x 以内，则 x 为合法解
  if (!cnt) return true;

  // 将子树所有的差分值通过 DFS 序累加到子树根上，得到经过子树根节点返祖边的链的数量
  for (int i = N; i; --i) diff[fa[ver[i]]] += diff[ver[i]];

  for (int i = 1; i <= N; ++i)
    // 如果经过某条边的链的数量与需覆盖链的数量相吻合，且该边边权足以将所有链长减小到 x 以内
    if (diff[i] == cnt && dist[i] - dist[fa[i]] >= maxDelta)
      return true;  // 则 x 为合法解

  return false;
}

int main() {
  N = read<int>(), M = read<int>();
  g.resize(N + 1);

  for (int i = 1, u, v, w; i < N; ++i) {
    u = read<int>(), v = read<int>(), w = read<int>();
    g[u].emplace_back(v, w);
    g[v].emplace_back(u, w);
  }

  DFS1(1, 0);
  DFS2(1, 1);

  for (int i = 1, u, v, lca; i <= M; ++i) {
    u = read<int>(), v = read<int>(), lca = qry_LCA(u, v);
    plans[i] = (Plan){u, v, lca, dist[u] + dist[v] - 2 * dist[lca]};
  }

  int l = 0, r = std::numeric_limits<int>::max();

  while (l < r) {
    int mid = (l + r) >> 1;
    if (check(mid)) r = mid;
    else l = mid + 1;
  }

  write(r), flush();
  return 0;
}
