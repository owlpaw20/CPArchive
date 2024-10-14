#include <bits/stdc++.h>

using f64 = double;

const int MAX_N = 2.5e3 + 5;
const f64 EPS = 1e-6;

int K, N;
f64 s[MAX_N], p[MAX_N];
std::vector<std::vector<int>> g;

int size[MAX_N];
f64 w[MAX_N], f[MAX_N][MAX_N];  // f[i][j] 表示以 i 为根节点的子树中选择了 j 个人的最大权值

bool check(f64 x) {
  for (int i = 1; i <= N; ++i) w[i] = p[i] - x * s[i];               // 初始化分数规划权值数组
  for (int i = 0; i <= N; ++i) std::fill(f[i], f[i] + K + 2, -1e9);  // 初始化 DP 数组

  auto DFS = [&](int u, auto&& DFS) -> void {
    f[u][1] = w[u], f[u][0] = 0;
    size[u] = 1;

    for (int v : g[u]) {
      DFS(v, DFS);
      size[u] += size[v];

      // 枚举当前节点选择的人数（根节点 u 必须选人，i >= 1）
      for (int i = size[u]; i; --i)
        // 枚举给子节点的子树分配的人数（根节点 u 必须选人，j <= i - 1）
        for (int j = 0; j <= std::min(size[v], i - 1); ++j)
          f[u][i] = std::max(f[u][i], f[u][i - j] + f[v][j]);  // 转移
    }
  };

  DFS(0, DFS);

  return f[0][K + 1] >= 0;
}

int main() {
  std::fixed(std::cout).precision(3);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> K >> N;
  g.resize(N + 1);

  for (int i = 1, x; i <= N; ++i) {
    std::cin >> s[i] >> p[i] >> x;
    g[x].push_back(i);
  }

  f64 l = 0, r = 1e4;

  while (fabs(r - l) > EPS) {
    f64 mid = (l + r) / 2;
    check(mid) ? l = mid : r = mid;
  }

  std::cout << l << std::flush;
  return 0;
}
