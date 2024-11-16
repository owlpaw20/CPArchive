#include <bits/stdc++.h>

using i64 = long long;
using TUP = std::tuple<int, int, int>;

const int MAX_N = 1e5 + 5;

int N, W, C;
std::vector<TUP> seg;
int d[MAX_N << 1], idx;

i64 sum;
i64 pre[MAX_N << 1], suf[MAX_N << 1];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> W >> C;
  seg.resize(N + 1);

  for (int i = 1, l, r, p; i <= N; ++i) {
    std::cin >> l >> r >> p, seg[i] = {l, r, p};
    d[++idx] = l, d[++idx] = r;
  }

  std::sort(d + 1, d + idx + 1);
  idx = std::unique(d + 1, d + idx + 1) - d - 1;

  for (int i = 1; i <= N; ++i) {
    auto [l, r, p] = seg[i];
    int dl = std::lower_bound(d + 1, d + idx + 1, l) - d;
    int dr = std::lower_bound(d + 1, d + idx + 1, r) - d;
    pre[dr] += p, suf[dl] += p, sum += p;
  }

  for (int i = 1; i <= idx; ++i) pre[i] += pre[i - 1];
  for (int i = idx; i >= 1; --i) suf[i] += suf[i + 1];

  auto get_cost = [&](int l, int r) -> i64 {
    int dl = std::upper_bound(d + 1, d + idx + 1, l) - d - 1;
    int dr = std::lower_bound(d + 1, d + idx + 1, r) - d;
    return sum - pre[dl] - suf[dr];
  };

  i64 ans = std::numeric_limits<i64>::max();

  for (int i = 1; i <= idx; ++i) {
    if (d[i] - C >= 0) ans = std::min(ans, get_cost(d[i] - C, d[i]));
    if (d[i] + C <= W) ans = std::min(ans, get_cost(d[i], d[i] + C));
  }

  std::cout << ans << std::flush;
  return 0;
}
