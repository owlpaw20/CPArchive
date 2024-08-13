#include <cstring>
#include <iostream>

const int MAX_N = 1e2 + 5;
const int MAX_M = 1e4 + 5;

int N, x, y;
int a[MAX_N], b[MAX_N];
int f[MAX_N][MAX_M][MAX_N];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> x >> y;
  for (int i = 1; i <= N; ++i) std::cin >> a[i] >> b[i];

  memset(f, 0x3F, sizeof f);
  f[0][0][0] = 0;

  for (int i = 1; i <= N; ++i)
    for (int j = 0; j <= x; ++j)
      for (int k = 0; k <= i; ++k) {
        f[i][j][k] = f[i - 1][j][k];
        if (j >= a[i] && k >= 1) f[i][j][k] = std::min(f[i][j][k], f[i - 1][j - a[i]][k - 1] + b[i]);
      }

  int ans = 0;
  for (int i = 0; i <= N; ++i)
    for (int j = 0; j <= x; ++j) {
      if (i == N && f[N][j][i] <= y) ans = std::max(ans, i);
      if (i < N && f[N][j][i] <= y) ans = std::max(ans, i + 1);
    }

  std::cout << ans << std::endl;
  return 0;
}
