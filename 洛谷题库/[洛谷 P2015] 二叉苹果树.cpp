#include <vector>
#include <iostream>

#define endl '\n'

using PII = std::pair<int, int>;

const int MAX_N = 1e2 + 5;

int n, q, cnt[MAX_N];
int f[MAX_N][MAX_N];  // f[i][j] 表示以 i 节点为根的子树内，保留 j 根树枝的方案数
std::vector<std::vector<PII>> graph;

void DFS(int u, int fa) {
  for (auto [v, w] : graph[u]) {
    if (v == fa) continue;
    DFS(v, u);
    cnt[u] += cnt[v] + 1;           // 保存当前子树内的边数
    for (int j = cnt[u]; j; --j)    // 枚举当前子树内保留的边数
      for (int k = j - 1; ~k; --k)  // 枚举给当前子节点为根的子树分配的边数
        f[u][j] = std::max(f[u][j], f[u][j - k - 1] + f[v][k] + w);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> q;
  graph.resize(n + 1);

  for (int i = 1, u, v, s; i < n; ++i) {
    std::cin >> u >> v >> s;
    graph[u].emplace_back(v, s);
    graph[v].emplace_back(u, s);
  }

  DFS(1, -1);

  std::cout << f[1][q] << endl;
  return fflush(stdout), 0;
}
