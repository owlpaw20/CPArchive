#include <bits/stdc++.h>

const int MAX_N = 1e4 + 5;
const int MAX_M = 1e3 + 5;
const int INF = 0x3F3F3F3F;

int N, M, K;
int a[MAX_N], b[MAX_N];
int lm[MAX_N], um[MAX_N];
int f[MAX_N][MAX_M << 1];  // f[x][y] 为到达 (x, y) 所需要的最小点击次数

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M >> K;
  memset(lm, 0xC0, sizeof(int) * (N + 1));
  memset(um, 0x3F, sizeof(int) * (N + 1));
  for (int i = 1; i <= N; ++i) std::cin >> a[i] >> b[i];
  for (int i = 1, x; i <= K; ++i) std::cin >> x >> lm[x] >> um[x];

  memset(f[0], 0, sizeof(int) * (M + 1));

  for (int i = 1; i <= N; ++i) {
    memset(f[i], 0x3F, sizeof(int) * (2 * M + 1));
    for (int j = a[i] + 1; j <= M + a[i]; ++j) f[i][j] = std::min(f[i - 1][j - a[i]] + 1, f[i][j - a[i]] + 1);
    for (int j = M + 1; j <= M + a[i]; ++j) f[i][M] = std::min(f[i][M], f[i][j]);
    for (int j = 1; j <= M - b[i]; ++j) f[i][j] = std::min(f[i][j], f[i - 1][j + b[i]]);
    for (int j = 1; j <= lm[i]; ++j) f[i][j] = INF;
    for (int j = um[i]; j <= M; ++j) f[i][j] = INF;
  }

  int ans = *std::min_element(&f[N][0], &f[N][M]);

  if (ans != INF) {
    std::cout << 1 << '\n';
    std::cout << ans << std::flush;
    return 0;
  }

  int cnt = 0;

  for (int i = 1; i <= N; ++i) {
    if (*std::min_element(&f[i][1], &f[i][M]) == INF) break;
    if (um[i] != INF) ++cnt;
  }

  std::cout << 0 << '\n';
  std::cout << cnt << std::flush;
  return 0;
}
