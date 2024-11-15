#include <bits/stdc++.h>

const int MAX_N = 1e2 + 5;
const int MAX_K = 15;
const int MOD = 1e8;

int N, M, p, q;
int f[MAX_N][MAX_N][MAX_K][2];  // f[i][j][k][0/1] 表示已经安排了 i 个步兵、j 个骑兵、队伍末尾有 k 个步兵/骑兵

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M >> p >> q;

  memset(f, 0, sizeof f);
  f[1][0][1][0] = f[0][1][1][1] = 1;

  for (int i = 0; i <= N; ++i)
    for (int j = 0; j <= M; ++j) {
      for (int k = 1; k <= p; ++k)
        if (f[i][j][k][0])
          (f[i][j + 1][1][1] += f[i][j][k][0]) %= MOD, (f[i + 1][j][k + 1][0] += f[i][j][k][0]) %= MOD;
      for (int k = 1; k <= q; ++k)
        if (f[i][j][k][1])
          (f[i + 1][j][1][0] += f[i][j][k][1]) %= MOD, (f[i][j + 1][k + 1][1] += f[i][j][k][1]) %= MOD;
    }

  int ans = 0;
  for (int i = 1; i <= p; ++i) (ans += f[N][M][i][0]) %= MOD;
  for (int i = 1; i <= q; ++i) (ans += f[N][M][i][1]) %= MOD;

  std::cout << ans << std::flush;
  return 0;
}
