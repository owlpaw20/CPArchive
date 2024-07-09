#include <cmath>
#include <iostream>

using l64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;

  while (T--) {
    l64 g, l;
    std::cin >> g >> l;
    std::cout << l64(sqrtl((__int128_t)g * l) * 2) << ' ';
    std::cout << g + l << '\n';
  }

  return fflush(stdout), 0;
}
