#include <bits/stdc++.h>

using i64 = long long;
using PII = std::pair<int, int>;

int N;
size_t K;

void solve() {
  std::cin >> N >> K;

  std::vector<PII> x(N);
  for (int i = 0; i < N; ++i) std::cin >> x[i].first;
  for (int i = 0; i < N; ++i) std::cin >> x[i].second;
  std::sort(x.begin(), x.end());

  i64 ans = std::numeric_limits<i64>::max(), sum = 0;
  std::priority_queue<int> heap;

  for (int i = 0; i < N; ++i) {
    auto [a, b] = x[i];
    if (heap.size() == K - 1) ans = std::min(ans, a * (sum + b));
    heap.push(b), sum += b;
    if (heap.size() > K - 1) sum -= heap.top(), heap.pop();
  }

  std::cout << ans << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) solve();

  return 0;
}
