#include <limits>
#include <cstdint>
#include <iostream>
#include <algorithm>

#define endl '\n'

using i64 = int64_t;

const int MAX_N = 3e3 + 5;

int N;
int a[MAX_N], b[MAX_N];
i64 f[MAX_N][MAX_N];
i64 g[MAX_N][MAX_N];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;

  for (int i = 1; i <= N; ++i)
    std::cin >> a[i], b[i] = a[i] -= i;

  std::sort(b + 1, b + N + 1);

  for (int i = 1; i <= N; ++i) {
    g[i][0] = std::numeric_limits<i64>::max();
    for (int j = 1; j <= N; ++j) {
      f[i][j] = g[i - 1][j] + abs(a[i] - b[j]);
      g[i][j] = std::min(g[i][j - 1], f[i][j]);
    }
  }

  std::cout << g[N][N] << endl;
  return fflush(stdout), 0;
}
