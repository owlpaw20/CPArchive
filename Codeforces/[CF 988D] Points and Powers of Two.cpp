#include <bits/stdc++.h>

using LL = long long;

const int MAX_N = 2e5 + 5;

int N, a[MAX_N];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  for (int i = 1; i <= N; ++i) std::cin >> a[i];

  std::sort(a + 1, a + N + 1);

  bool flag = false;
  int x = 0, y = 0;

  for (int i = 1; i <= N; ++i) {
    for (LL j = 1; j + a[i] <= std::numeric_limits<int>::max(); j <<= 1) {
      if (!std::binary_search(a + 1, a + N + 1, a[i] + j)) continue;

      if (std::binary_search(a + 1, a + N + 1, a[i] + j + j)) {
        std::cout << 3 << '\n';
        std::cout << a[i] << ' ' << a[i] + j << ' ' << a[i] + j + j << '\n';
        return 0;
      }

      if (!flag) {
        flag = true;
        x = a[i], y = a[i] + j;
      }
    }
  }

  if (flag) {
    std::cout << 2 << '\n';
    std::cout << x << ' ' << y << '\n';
    return 0;
  }

  std::cout << 1 << '\n';
  std::cout << a[1] << '\n';
  return 0;
}
