#include <bitset>
#include <cstring>
#include <iostream>
#include <vector>

const int MAX_N = 55;

int N, M, g1, g2, s1, s2;
int gg[MAX_N][MAX_N];
int g[MAX_N], b[MAX_N];

long long f[MAX_N][MAX_N][MAX_N], ans;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;
  memset(gg, 0x3F, sizeof gg);
  for (int i = 1; i <= N; ++i) gg[i][i] = 0;

  while (M--) {
    int u, v, w;
    std::cin >> u >> v >> w;
    gg[u][v] = gg[v][u] = w;
  }

  std::cin >> g1 >> g2 >> s1 >> s2;

  for (int k = 1; k <= N; ++k)
    for (int i = 1; i <= N; ++i)
      for (int j = 1; j <= N; ++j)
        gg[i][j] = std::min(gg[i][j], gg[i][k] + gg[k][j]);

  for (int i = 1; i <= N; ++i)
    for (int j = 1; j <= N; ++j)
      gg[i][j] = gg[i][j] * N + i;

  memset(g, 0x3F, sizeof(int) * (N + 1));

  for (int i = 1; i <= N; ++i)
    for (int j = 1; j <= N; ++j)
      if (i != j)
        g[i] = std::min(g[i], gg[i][j]), b[i] = std::max(b[i], gg[i][j]);

  for (int u = 1; u <= N; ++u)
    for (int v = 1; v <= N; ++v) {
      if (u == v) continue;

      memset(f, 0, sizeof f), f[0][0][0] = 1;
      std::vector<std::bitset<3>> medal(N + 1);

      for (int i = 1; i <= N; ++i)
        if (i == u) medal[i].set(0);
        else if (i == v) medal[i].set(2);
        else
          for (int j = 1; j <= N; ++j) {
            if (i == j) continue;
            if (gg[i][j] <= g[u]) medal[i].set(0);
            if (gg[i][j] > g[u] && gg[i][j] < b[v]) medal[i].set(1);
            if (gg[i][j] >= b[v]) medal[i].set(2);
          }

      for (int i = 1; i <= N; ++i)
        for (int j = 0; j <= i; ++j)
          for (int k = 0; j + k <= i; ++k) {
            if (j && medal[i].test(0)) f[i][j][k] += f[i - 1][j - 1][k];
            if (k && medal[i].test(1)) f[i][j][k] += f[i - 1][j][k - 1];
            if (medal[i].test(2)) f[i][j][k] += f[i - 1][j][k];
          }

      for (int i = g1; i <= g2; ++i)
        for (int j = s1; j <= s2; ++j)
          ans += f[N][i][j];
    }

  std::cout << ans << '\n';
  return 0;
}
