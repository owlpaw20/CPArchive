#include <bits/stdc++.h>

using LL = long long;

const int MAX_N = 2e5 + 5;
const int MAX_D = 19;

int N;
LL d[MAX_D][MAX_N];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;

  auto count = [](LL x) -> int {
    int sum = 0;
    for (; x; x /= 10) sum += x % 10;
    return sum;
  };

  LL ans = 0;

  for (int i = 1; i <= N; ++i) {
    static LL x;
    std::cin >> x;
    ans += count(x);
    for (LL j = 1, k = 10; j < MAX_D; ++j, k *= 10) d[j][i] = x % k;
  }

  ans *= 2 * N;

  for (int i = 1; i < MAX_D; ++i) std::sort(d[i] + 1, d[i] + N + 1);

  LL carry = 0;

  for (LL i = 1, k = 10; i < MAX_D; ++i, k *= 10)
    for (int j = 1; j <= N; ++j)
      carry += d[i] + N + 1 - std::lower_bound(d[i] + 1, d[i] + N + 1, k - d[i][j]);

  std::cout << ans - 9LL * carry << std::flush;
  return 0;
}
