#include <vector>
#include <iostream>
#include <algorithm>

#define endl '\n'

const int MAX_N = 1.5e3 + 5;
const int INF = 1e9;

int n, val[MAX_N];
std::vector<int> graph[MAX_N];
bool is_child[MAX_N];

// f[i] 表示节点 i 被其父节点所安排的守卫看守住，自己不安排守卫时的最小花费
// g[i] 表示节点 i 被其子节点所安排的守卫看守住，自己不安排守卫时的最小花费
// h[i] 表示节点 i 被自己安排的守卫看守住时的最小花费

/*
  f[i] = sum{min{g[j], h[j]}}
    父节点可以看守当前节点时，
    当前子节点可以看守自己，
    也可以被自己的子节点看住，
    根据定义，当前节点处不安排守卫。

  h[i] = val[i] + sum{min{f[j], g[j], h[j]}}
    当前节点自己看守自己时，
    首先需要加上在当前位置安排一个守卫的权值，
    此时自己的子节点可以均被父节点看守，自己不安排守卫，
    也可以被子节点看守，自己不安排守卫，
    也可以自己安排守卫看守自己。

  g[i] = min{val[j] + h[j] - sum{min{g[j], h[j]}}}
    当前节点被某一子节点看守时，
    枚举是被哪一个子节点看守了，
    从所有子节点的不被父节点看守的状态中，
    减去较优的子节点对应的状态，
    并在这个子节点上固定一位守卫。
*/

int f[MAX_N], g[MAX_N], h[MAX_N];

void DFS(const int u) {
  f[u] = 0;
  g[u] = INF;
  h[u] = val[u];

  for (int v : graph[u]) {
    DFS(v);
    f[u] += std::min(g[v], h[v]);
    h[u] += std::min({f[v], g[v], h[v]});
  }

  for (int v : graph[u])
    g[u] = std::min(g[u], f[u] - std::min(g[v], h[v]) + h[v]);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n;

  for (int i = 1, u, m, k; i <= n; ++i) {
    std::cin >> u >> k >> m;
    val[u] = k;
    for (int j = 1, v; j <= m; ++j) {
      std::cin >> v, is_child[v] = true;
      graph[u].push_back(v);
    }
  }

  for (int i = 1; i <= n; ++i)
    if (!is_child[i]) {
      DFS(i);
      std::cout << std::min(g[i], h[i]) << endl;
      break;
    }

  return fflush(stdout), 0;
}
