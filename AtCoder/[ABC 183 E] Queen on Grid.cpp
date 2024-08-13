#include <bits/stdc++.h>

const int MAX_N = 2e3 + 5;
const int MOD = 1e9 + 7;

int N, M;
int f[MAX_N][MAX_N];
int p[MAX_N][MAX_N][3];
bool a[MAX_N][MAX_N];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;

  for (int i = 1; i <= N; ++i)
    for (int j = 1; j <= M; ++j) {
      static char c;
      std::cin >> c;
      a[i][j] = (c == '#');
    }

  f[1][1] = 1;
  a[1][1] = true;
  p[1][1][0] = p[1][1][1] = p[1][1][2] = 1;

  for (int i = 1; i <= N; ++i)
    for (int j = 1; j <= M; ++j)
      if (!a[i][j]) {
        f[i][j] = ((uint32_t)p[i - 1][j][0] + p[i][j - 1][1] + p[i - 1][j - 1][2]) % MOD;
        p[i][j][0] = (p[i - 1][j][0] + f[i][j]) % MOD;
        p[i][j][1] = (p[i][j - 1][1] + f[i][j]) % MOD;
        p[i][j][2] = (p[i - 1][j - 1][2] + f[i][j]) % MOD;
      }

  std::cout << f[N][M] << std::flush;
  return 0;
}
