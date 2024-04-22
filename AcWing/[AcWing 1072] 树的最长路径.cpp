#include <cstring>
#include <iostream>

#define endl '\n'

const int MAX_N = 1e4 + 5;
const int MAX_M = 2e4 + 5;

int n;
int ed[MAX_M], nx[MAX_M], wt[MAX_M];
int dist[MAX_N], head[MAX_N], idx;

int f[MAX_N], g[MAX_N];
// f[i] 存经过点 i 的最大距离
// g[i] 存经过点 i 的次大距离

inline void connect(int u, int v, int w) {
  ed[idx] = v;
  wt[idx] = w;
  nx[idx] = head[u];
  head[u] = idx++;
}

void DFS(const int u, const int fa) {
  for (int i = head[u], v; ~i; i = nx[i]) {
    if ((v = ed[i]) == fa) continue;
    DFS(v, u);
    if (f[u] <= f[v] + wt[i]) {      // 如果当前距离大于或等于原最大距离
      g[u] = f[u];                   // 视原最大距离为当前次大距离
      f[u] = f[v] + wt[i];           // 更新当前最大距离
    } else if (g[u] < f[v] + wt[i])  // 如果当前距离小于原最大距离但大于原次大距离
      g[u] = f[v] + wt[i];           // 更新原次大距离
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  memset(head, -1, sizeof head);

  std::cin >> n;

  for (int i = 1, u, v, w; i < n; ++i) {
    std::cin >> u >> v >> w;
    connect(u, v, w);
    connect(v, u, w);
  }

  DFS(1, -1);

  int ans = 0;
  for (int i = 1; i <= n; ++i)         // 遍历每个点
    ans = std::max(ans, f[i] + g[i]);  // 统计经过每个点的最长路径

  std::cout << ans << endl;
  return fflush(stdout), 0;
}
