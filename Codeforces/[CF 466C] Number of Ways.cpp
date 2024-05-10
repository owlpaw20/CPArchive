#include <numeric>
#include <iostream>

using l64 = long long;

const int MAX_N = 5e5 + 5;

int N;
l64 a[MAX_N];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  for (int i = 1; i <= N; ++i) std::cin >> a[i], a[i] += a[i - 1];

  if (a[N] % 3 || N < 3) {
    std::cout << 0 << '\n';
    return fflush(stdout), 0;
  }

  l64 part_sum = a[N] / 3;
  l64 cnt = 0, ans = 0;

  for (int i = 1; i <= N; ++i) {
    if (a[i] == 2 * part_sum && i > 1 && i < N) ans += cnt;
    if (a[i] == part_sum) ++cnt;
  }

  std::cout << ans << '\n';
  return fflush(stdout), 0;
}
