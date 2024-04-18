#include <iostream>

#define endl '\n'

const int MAX_N = 1e5 + 5;

int n;
int c[MAX_N], a[MAX_N];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n;
  for (int i = 1; i <= n; ++i) std::cin >> c[i];

  if (n & 1) {
    for (int i = 1; i <= n; ++i)
      if (c[i] & 1) std::cout << (a[i] = ((c[i] + n) >> 1)) << ' ';
      else std::cout << (a[i] = (c[i] >> 1)) << ' ';
    std::cout.put('\n');

    for (int i = 1; i <= n; ++i) std::cout << a[i] << ' ';
    std::cout.put('\n');
  } else
    std::cout << -1 << endl;

  return fflush(stdout), 0;
}
