#include <cstring>
#include <iostream>

#define endl '\n'

const int MAX_N = 1e4 + 5;
const int MAX_M = 2e4 + 5;
const int INF = 2e9;

int n, a[MAX_N], b[MAX_N];

int ed[MAX_M], nx[MAX_M], wt[MAX_M];
int head[MAX_N], idx;

/*
  f[i] 存储从节点 i 向叶节点走的最远距离
  g[i] 存储从节点 i 向叶节点走的次远距离
  p[i] 存储从节点 i 向叶节点走的最远距离对应路径上碰到的第一个子节点
  h[i] 存储从节点 i 向根节点走的最远距离
*/

int f[MAX_N], g[MAX_N], p[MAX_N];
int h[MAX_N];

bool is_leaf[MAX_N];

inline void connect(const int u, const int v, const int w) {
  ed[idx] = v;
  wt[idx] = w;
  nx[idx] = head[u];
  head[u] = idx++;
}

int DFS_to_leaf(const int u, const int fa) {
  f[u] = g[u] = -INF;

  for (int i = head[u], v, dist; ~i; i = nx[i]) {
    if ((v = ed[i]) == fa) continue;

    // 当前需要判断的距离为子节点到叶节点的最远距离加上当前这条边的长度
    dist = DFS_to_leaf(v, u) + wt[i];

    if (dist >= f[u]) {      // 如果当前距离大于或等于当前节点原最远距离
      g[u] = f[u];           // 视原最远距离为当前次远距离
      f[u] = dist;           // 更新当前最远距离
      p[u] = v;              // 更新最远距离所在路径经过的第一个子节点
    } else if (dist > g[u])  // 如果当前距离小于原最远距离但大于原次远距离
      g[u] = dist;           // 更新当前次远距离
  }

  // 如果当前节点的最远距离没有被更新，说明当前节点为叶节点
  if (f[u] == -INF) {
    f[u] = g[u] = 0;
    is_leaf[u] = true;
  }

  return f[u];
}

void DFS_to_root(const int u, const int fa) {
  for (int i = head[u], v; ~i; i = nx[i]) {
    if ((v = ed[i]) == fa) continue;

    // 如果当前子节点在当前节点的最远距离对应路径上，则用当前子节点的次远距离更新
    h[v] = std::max(h[u], (p[u] == v) ? g[u] : f[u]) + wt[i];

    DFS_to_root(v, u);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  memset(head, -1, sizeof head);

  std::cin >> n;

  for (int i = 1, u, v, w; i <= n; ++i) {
    std::cin >> u >> v >> w;
    connect(u, v, w);
    connect(v, u, w);
  }

  DFS_to_leaf(1, -1);
  DFS_to_root(1, -1);

  int ans = f[1];  // 根节点根据定义不用 h[i] 更新
  for (int i = 2; i <= n; ++i)
    if (is_leaf[i]) ans = std::min(ans, h[i]);  // 叶节点根据定义不用 f[i] 更新
    else ans = std::min(ans, std::max(h[i], f[i]));

  std::cout << ans << endl;
  return fflush(stdout), 0;
}
