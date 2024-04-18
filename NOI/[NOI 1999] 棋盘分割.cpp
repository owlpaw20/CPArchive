#include <cmath>
#include <iostream>

#define endl '\n'

using c32 = const int;
using f64 = double;

int N;
int p[9][9];
f64 f[9][9][9][9][16];
// f[i][j][k][l][m] = 将 (i, j) 到 (k, l) 的矩形分成 m 份的最小方案

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.precision(3);

  std::cin >> N;
  for (int i = 1; i <= 8; ++i)
    for (int j = 1; j <= 8; ++j) {
      std::cin >> p[i][j];
      p[i][j] += p[i - 1][j] + p[i][j - 1] - p[i - 1][j - 1];
    }

  f64 avg = p[8][8] * 1.0 / N;

  auto calc = [&](c32 x1, c32 y1, c32 x2, c32 y2) -> f64 {
    f64 sum = p[x2][y2] - p[x1 - 1][y2] - p[x2][y1 - 1] + p[x1 - 1][y1 - 1] - avg;
    return sum * sum / N;
  };

  for (int i = 1; i <= N; ++i)
    for (int x1 = 1; x1 <= 8; ++x1)
      for (int y1 = 1; y1 <= 8; ++y1)
        for (int x2 = 1; x2 <= 8; ++x2)
          for (int y2 = 1; y2 <= 8; ++y2) {
            f64 &state = f[x1][y1][x2][y2][i];
            state = 1e9;

            if (i == 1)
              state = calc(x1, y1, x2, y2);
            else {
              for (int j = x1; j < x2; ++j) {
                state = std::min(state, f[x1][y1][j][y2][i - 1] + calc(j + 1, y1, x2, y2));
                state = std::min(state, f[j + 1][y1][x2][y2][i - 1] + calc(x1, y1, j, y2));
              }
              for (int j = y1; j < y2; ++j) {
                state = std::min(state, f[x1][y1][x2][j][i - 1] + calc(x1, j + 1, x2, y2));
                state = std::min(state, f[x1][j + 1][x2][y2][i - 1] + calc(x1, y1, x2, j));
              }
            }
          }

  std::cout << std::fixed << sqrt(f[1][1][8][8][N]) << endl;
  return fflush(stdout), 0;
}
