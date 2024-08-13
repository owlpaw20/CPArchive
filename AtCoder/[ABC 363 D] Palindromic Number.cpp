#include <bits/stdc++.h>

using LL = long long;

LL k;
LL p10[20];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  p10[0] = 1;
  for (int i = 1; i <= 18; ++i) p10[i] = p10[i - 1] * 10;

  std::cin >> k;

  if (!--k) {
    std::cout << 0 << std::endl;
    return 0;
  }

  while (true) {
    static int digits = 1;
    int half = (digits + 1) / 2;

    if (k > 9 * p10[half - 1]) {
      k -= 9 * p10[half - 1];
      ++digits;
      continue;
    }

    std::string ans1 = std::to_string(p10[half - 1] + k - 1);
    std::string ans2 = std::string(digits & 1 ? ++ans1.rbegin() : ans1.rbegin(), ans1.rend());
    std::cout << ans1 + ans2 << std::endl;
    break;
  }

  return 0;
}
