#include <vector>
#include <iostream>
#include <algorithm>

using LL = long long;
const int MAX_N = 1e5 + 5;

int N, q;
std::vector<int> a;

bool check(LL mid, int b, int k) {
  auto lb = std::lower_bound(a.begin(), a.end(), b - mid);
  auto rb = std::upper_bound(a.begin(), a.end(), b + mid);
  return rb - lb < k;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> q;
  for (int i = 1, x; i <= N; ++i) std::cin >> x, a.push_back(x);
  std::sort(a.begin(), a.end());

  while (q--) {
    static int b, k;
    std::cin >> b >> k;

    LL l = 0, r = 1e18;
    while (l < r) {
      LL mid = (l + r) >> 1;
      if (check(mid, b, k)) l = mid + 1;
      else r = mid;
    }

    std::cout << r << '\n';
  }

  return 0;
}
