#include <iostream>

#define endl '\n'

using l64 = long long int;

const l64 INF = 1e18;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  l64 a, b;
  std::cin >> a >> b;
  
  l64 l = -INF, r = INF;

  while (l < r) {
    l64 mid = l + (r - l) / 2;
    if (a + b > mid) l = mid + 1;
    else r = mid;
  }

  std::cout << r << endl;
  fflush(stdout);
  return 0;
}
