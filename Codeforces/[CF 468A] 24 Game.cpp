#pragma GCC optimize("O2,unroll-loops,inline")

#include <iostream>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int N;
  std::cin >> N;

  if (N < 4) {
    std::cout << "NO" << std::endl;
    exit(0);
  }

  std::cout << "YES" << std::endl;

  if (N & 1) {
    std::cout << "5 - 1 = 4\n";
    std::cout << "4 - 2 = 2\n";
    std::cout << "2 * 3 = 6\n";
    std::cout << "4 * 6 = 24\n";
    for (int i = 6; i <= N; i += 2) {
      std::cout << i + 1 << " - " << i << " = 1\n";
      std::cout << "1 * 24 = 24" << '\n';
    }
  } else {
    std::cout << "1 + 2 = 3\n";
    std::cout << "3 + 3 = 6\n";
    std::cout << "4 * 6 = 24\n";
    for (int i = 5; i <= N; i += 2) {
      std::cout << i + 1 << " - " << i << " = 1\n";
      std::cout << "1 * 24 = 24" << '\n';
    }
  }

  return fflush(stdout), 0;
}
