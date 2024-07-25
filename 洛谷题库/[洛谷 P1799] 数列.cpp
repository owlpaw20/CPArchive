#include <iostream>
#include <algorithm>

constexpr int MAX_N = 1e3 + 5;

int N, a[MAX_N];
int f[MAX_N][MAX_N];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  for (int i = 1; i <= N; ++i) std::cin >> a[i];

  for (int i = 1; i <= N; ++i)
    for (int j = 1; j <= i; ++j)
      f[i][j] = std::max(f[i - 1][j], f[i - 1][j - 1] + (a[i] == j));

  std::cout << *std::max_element(f[N] + 1, f[N] + N + 1) << std::endl;
  return 0;
}
