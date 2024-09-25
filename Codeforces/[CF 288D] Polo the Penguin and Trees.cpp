#include <bits/stdc++.h>

using i64 = long long;

const int MAX_N = 8e4 + 5;

int N;
std::vector<std::vector<int>> g;

i64 choose_2(i64 x) { return x * (x - 1) / 2; }

int size[MAX_N];
i64 ans;

// DFS 求出两条链在 u 相交的方案数
void DFS(int u) {
  size[u] = 1;
  i64 sts = 0;  // 两个端点分别在当前节点任意两个不同子节点的子树中的链的情况数
  i64 ito = 0;  // 两个端点分别在当前节点子树内和子树外的链的情况数

  for (int v : g[u]) {
    if (size[v]) continue;
    DFS(v), size[u] += size[v];
    sts -= choose_2(size[v]);  // 去除两个端点在同一个子节点的子树内的情况
  }

  sts += choose_2(size[u]);          // 这是在子树内任选两个端点的链的总方案数
  ito = size[u] * (N - size[u]);     // 根据定义计算即可
  ans += sts * sts + sts * ito * 2;  // 两条链都在子树内，或一条在子树内、一条跨子树根
}

// 为何不考虑所有两条路径的端点都是一条在子树内，一条在子树外？
// 因为这种情况会在当前节点统计一次，由于在父节点处相交就会又在父节点处统计一次，造成重复

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  g.resize(N + 1);

  for (int i = 1, u, v; i < N; ++i) {
    std::cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  DFS(1);

  std::cout << choose_2(N) * choose_2(N) - ans << std::flush;
  return 0;
}
