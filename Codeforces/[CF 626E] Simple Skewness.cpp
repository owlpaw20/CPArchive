#include <bits/stdc++.h>

using i64 = long long;
using f128 = long double;

const int MAX_N = 2e5 + 5;

int N, x[MAX_N];
i64 sumX[MAX_N];

// 写 EPS 会寄

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  for (int i = 1; i <= N; ++i) std::cin >> x[i];
  std::sort(x + 1, x + N + 1);
  std::inclusive_scan(x + 1, x + N + 2, sumX + 1, std::plus<>(), 0LL);

  auto avg = [&](int i, int k) -> f128 {
    if (i - k - 1 < 0) return std::numeric_limits<i64>::min();
    f128 sum = (sumX[i] - sumX[i - k - 1]) + (sumX[N] - sumX[N - k]);
    return sum / (2 * k + 1);
  };

  f128 max = 0;
  int maxI = -1, maxK = -1;

  for (int i = 1; i <= N; ++i) {
    int l = 1, r = std::min(i - 1, N - i);

    while (l < r) {
      int mid = (l + r) >> 1;
      avg(i, mid) > avg(i, mid + 1) == 1 ? r = mid : l = mid + 1;
    }

    if (max < avg(i, r) - x[i]) {
      max = avg(i, r) - x[i];
      maxI = i, maxK = r;
    }
  }

  if (max == 0) {
    std::cout << 1 << '\n';
    std::cout << x[1] << '\n';
    return 0;
  }

  std::cout << 2 * maxK + 1 << '\n';

  for (int i = maxI - maxK; i <= maxI; ++i) std::cout << x[i] << ' ';
  for (int i = N - maxK + 1; i <= N; ++i) std::cout << x[i] << ' ';
  return 0;
}
