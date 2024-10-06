#include <bits/stdc++.h>

using i64 = long long;

const int MAX_N = 1e5 + 5;
const int MAX_K = 1e2 + 5;
const int MOD = 1e9 + 7;

int N, K;
std::vector<std::vector<int>> g;

int f[MAX_N][MAX_K][2][2];
i64 buf[MAX_K][2][2];

// f[u][i][x][y] 表示 u 的子树中放置了 i 个装置使得子树中除 u 之外的所有节点均被监听
// x 为 u 点是否放置了装置，y 为 u 点是否被监听

int size[MAX_N];

void DFS(int u, int fa) {
  size[u] = 1;
  f[u][0][0][0] = f[u][1][1][0] = 1;  // 初始化

  for (int v : g[u]) {
    if (v == fa) continue;
    DFS(v, u);

    for (int i = 0; i <= std::min(size[u], K); ++i)
      for (int j = 0; j < 2; ++j)
        for (int k = 0; k < 2; ++k)
          buf[i][j][k] = f[u][i][j][k], f[u][i][j][k] = 0;

    for (int i = 0; i <= std::min(size[u], K); ++i)
      for (int j = 0; j <= std::min(size[v], K - i); ++j) {
        auto &tar = f[u][i + j], &fv = f[v][j];
        auto &fu = buf[i];

        tar[0][0] += fu[0][0] * fv[0][1] % MOD;
        tar[1][0] += fu[1][0] * (fv[0][0] + fv[0][1]) % MOD;
        tar[0][1] += (fu[0][0] * fv[1][1] + fu[0][1] * (fv[0][1] + fv[1][1])) % MOD;
        tar[1][1] += (fu[1][0] * (fv[1][0] + fv[1][1]) + fu[1][1] * ((i64)fv[0][0] + fv[0][1] + fv[1][0] + fv[1][1])) % MOD;

        for (int k = 0; k < 2; ++k)
          for (int l = 0; l < 2; ++l)
            tar[k][l] %= MOD;
      }

    size[u] += size[v];
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> K;
  g.resize(N + 1);

  for (int i = 1, u, v; i < N; ++i) {
    std::cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  DFS(1, 0);

  std::cout << (f[1][K][0][1] + f[1][K][1][1]) % MOD << std::flush;
  return 0;
}
