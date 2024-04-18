#include <cmath>
#include <tuple>
#include <cstdint>
#include <numeric>
#include <iostream>
#include <algorithm>

#define endl '\n'

using i64 = int64_t;
using PII = std::pair<i64, i64>;
using TUP = std::tuple<int, int, int>;

using std::get;

constexpr int MAX_N = 5e4 + 5;
constexpr int MAX_B = 2e2 + 50;

int c[MAX_N], bel[MAX_N], cnt[MAX_N];
TUP qry[MAX_N];
PII ans[MAX_N];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int N, M, block;
  std::cin >> N >> M, block = sqrt(N);
  for (int i = 1; i <= N; ++i)
    std::cin >> c[i], bel[i] = (i - 1) / block + 1;

  for (int i = 0; i < M; ++i) {
    auto& [l, r, j] = qry[i];
    std::cin >> l >> r, j = i;
  }

  std::sort(qry, qry + M, [&](const TUP& x, const TUP& y) -> bool {
    if (bel[get<0>(x)] != bel[get<0>(y)]) return bel[get<0>(x)] < bel[get<0>(y)];
    if (bel[get<0>(x)] & 1) return get<1>(x) > get<1>(y);
    return get<1>(x) < get<1>(y);
  });

  i64 sum = 0;
  auto expand = [&](const int x) -> void { sum += cnt[x]++; };
  auto shrink = [&](const int x) -> void { sum -= --cnt[x]; };
  auto frac = [](i64 x, i64 y) -> PII {
    if (x == 0) return PII(0, 1);
    i64 g = std::gcd(x, y);
    return PII(x / g, y / g);
  };

  for (int i = 0, l = 1, r = 0; i < M; ++i) {
    auto [ql, qr, qi] = qry[i];

    if (ql == qr) {
      ans[qi] = PII(0, 1);
      continue;
    }

    while (l > ql) expand(c[--l]);
    while (r < qr) expand(c[++r]);
    while (l < ql) shrink(c[l++]);
    while (r > qr) shrink(c[r--]);

    ans[qi] = frac(sum, ((r - l + 1LL) * (r - l)) >> 1);
  }

  for (int i = 0; i < M; ++i)
    std::cout << ans[i].first << '/' << ans[i].second << endl;

  return fflush(stdout), 0;
}
