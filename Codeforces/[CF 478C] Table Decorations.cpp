#include <iostream>
#include <algorithm>

using l64 = long long;

l64 a, b, c;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> a >> b >> c;
  std::cout << std::min({(a + b + c) / 3, a + b, b + c, a + c}) << '\n';

  return fflush(stdout), 0;
}
