#include <cmath>
#include <iostream>

using FL = double;

const int MAX_N = 15;

int N;
FL a[MAX_N][MAX_N], b[MAX_N][MAX_N];

void GaussJordan() {
  for (int r = 1, c = 1, max_r; c <= N; ++r, ++c) {
    max_r = r;
    for (int i = r; i <= N; ++i) (fabs(b[i][c]) > fabs(b[max_r][c])) && (max_r = i);
    for (int i = c; i <= N + 1; ++i) std::swap(b[max_r][i], b[r][i]);
    for (int i = N + 1; i >= c; --i) b[r][i] /= b[r][c];
    for (int i = r + 1; i <= N; ++i)
      for (int j = N + 1; j >= c; --j)
        b[i][j] -= b[r][j] * b[i][c];
  }

  for (int i = N; i > 1; --i)
    for (int j = i - 1; j; --j)
      b[j][N + 1] -= b[i][N + 1] * b[j][i], b[j][i] = 0;
}

int main() {
  std::fixed(std::cout).precision(3);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;

  for (int i = 0; i <= N; ++i)
    for (int j = 1; j <= N; ++j)
      std::cin >> a[i][j];

  for (int i = 1; i <= N; ++i)
    for (int j = 1; j <= N; ++j) {
      b[i][j] = 2 * (a[i][j] - a[0][j]);
      b[i][N + 1] += a[i][j] * a[i][j] - a[0][j] * a[0][j];
    }

  GaussJordan();

  for (int i = 1; i <= N; ++i) std::cout << b[i][N + 1] << ' ';

  std::cout.flush();
  return 0;
}
