#include <vector>
#include <iostream>

#define endl '\n'

const int MAX_N = 1.5e3 + 5;

int n;
std::vector<int> graph[MAX_N];

// f[i] 表示在以 i 为根节点的子树中不选 i 的最小花费
// g[i] 表示在以 i 为根节点的子树中选 i 的最小花费
int f[MAX_N], g[MAX_N];

void DFS(const int u, const int fa) {
  f[u] = 0, g[u] = 1;  // 初始情况
  for (int v : graph[u])
    if (v != fa) {
      DFS(v, u);
      f[u] += g[v];                  // 如果当前节点不选，则这条边的另一个端点必须选
      g[u] += std::min(f[v], g[v]);  // 如果当前节点选了，则这条边的另一个端点可选可不选
    }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n;

  for (int i = 1, u, k; i <= n; ++i) {
    std::cin >> u >> k;
    for (int j = 1, v; j <= k; ++j) {
      std::cin >> v;
      graph[u].push_back(v);
      graph[v].push_back(u);
    }
  }

  DFS(1, -1);

  std::cout << std::min(f[1], g[1]) << endl;
  return fflush(stdout), 0;
}
