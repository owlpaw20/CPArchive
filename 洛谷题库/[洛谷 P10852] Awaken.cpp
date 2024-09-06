#include <bits/stdc++.h>

using PII = std::pair<int, int>;

int N, M;
std::vector<PII> p;

void solve() {
  std::cin >> N >> M;
  p = std::vector<PII>();

  for (int i = 1, x, y; i <= M; ++i) {
    std::cin >> x >> y;
    p.emplace_back(x, y);
  }

  if (M <= 1)
    return puts("Yes"), void();

  std::sort(p.begin(), p.end());

  int val_d = (p.back().second - p.front().second);
  int idx_d = (p.back().first - p.front().first);

  if (val_d % idx_d)
    return puts("No"), void();

  int d = val_d / idx_d;

  for (size_t i = 1; i < p.size(); ++i)
    if (p[i].second - p[i - 1].second != d * (p[i].first - p[i - 1].first))
      return puts("No"), void();

  puts("Yes");
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) solve();

  return 0;
}
