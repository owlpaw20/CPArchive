#include <bits/stdc++.h>

using PII = std::pair<int, int>;

const int MAX_N = 1e5 + 5;

int N;
PII w[MAX_N];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> N;
  for (int i = 1; i <= N; ++i) std::cin >> w[i].first >> w[i].second;
  std::sort(w + 1, w + N + 1, [](PII x, PII y) { return x.second < y.second; });

  int ans = 0;

  for (int i = 1, max_r = 1; i <= N; ++i)
    if (w[i].first >= max_r)
      max_r = w[i].second, ++ans;

  std::cout << ans << std::flush;
  return 0;
}
