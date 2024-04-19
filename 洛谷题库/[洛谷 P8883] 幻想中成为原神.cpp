#include <cmath>
#include <iostream>

#define endl '\n'

using i64 = long long int;
using f128 = long double;

const f128 PI = acosl(-1);
const f128 BASE = (1.0 - 6.0 / PI / PI);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    i64 n;
    std::cin >> n;
    std::cout << i64(BASE * n) << endl;
  }

  return fflush(stdout), 0;
}
