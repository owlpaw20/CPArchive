#include <iostream>
#include <algorithm>

using LL = long long;
using PII = std::pair<int, int>;

const int MAX_N = 2e5 + 5;

int N;
LL x, y;
PII dish[MAX_N];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> x >> y;
  for (int i = 1; i <= N; ++i) std::cin >> dish[i].first;
  for (int i = 1; i <= N; ++i) std::cin >> dish[i].second;

  std::sort(dish + 1, dish + N + 1, std::greater<PII>());

  LL sumX = 0, sumY = 0;
  int ans1 = N;

  for (int i = 1; i <= N; ++i) {
    sumX += dish[i].first;
    sumY += dish[i].second;
    if (sumX > x || sumY > y) {
      ans1 = i;
      break;
    }
  }

  std::sort(dish + 1, dish + N + 1, [&](PII x, PII y) { return x.second > y.second; });

  sumX = 0, sumY = 0;
  int ans2 = N;

  for (int i = 1; i <= N; ++i) {
    sumX += dish[i].first;
    sumY += dish[i].second;
    if (sumX > x || sumY > y) {
      ans2 = i;
      break;
    }
  }

  std::cout << std::min(ans1, ans2) << std::endl;
  return 0;
}
