#include <bits/stdc++.h>

using f64 = double;
using PII = std::pair<int, int>;
using PFF = std::pair<f64, f64>;

const f64 EPS = 1e-10;
const f64 MARGIN = 1e-5;

int N, M;
f64 L, V;

int fcmp(f64 x, f64 y) {
  if (fabs(x - y) <= EPS) return 0;
  return x > y ? 1 : -1;
}

PFF get_speeding_interval(f64 st_x, f64 st_v, int a) {
  f64 ed_x = (a >= 0) ? L : st_x + (st_v * st_v * 1.0 / (-2 * a));

  if (a == 0) {                            // 如果匀速
    if (st_v > V) return PFF(st_x, ed_x);  // 初速度超速则全程超速
    return PFF(-1, -1);                    // 否则全程不超速
  }

  else if (a > 0) {                                           // 如果匀加速
    if (fcmp(st_v, V) == 1) return PFF(st_x, ed_x);           // 初速度超速则全程超速
    if (fcmp(st_v, V) == 0) return PFF(st_x + MARGIN, ed_x);  // 初速度等于限速则除出发点外全程超速

    f64 spd_x = (V * V - st_v * st_v) / (2 * a);                // 计算要达到限速所需要的位移
    if (fcmp(st_x + spd_x, ed_x) == 1) return PFF(-1, -1);      // 如果达到该位移已经超过道路范围，则全程不超速
    if (fcmp(st_x + spd_x, ed_x) == 0) return PFF(ed_x, ed_x);  // 如果刚好在末端到达该位移，则在结束点超速
    return PFF(st_x + spd_x + MARGIN, ed_x);                    // 否则在达到该位移后全程超速
  }

  else {                                          // 如果匀减速
    if (fcmp(V, st_v) != -1) return PFF(-1, -1);  // 初速度不超速则全程不超速

    f64 spd_x = (V * V - st_v * st_v) / (2 * a);                         // 计算要降至限速所需要的位移
    if (fcmp(st_x + spd_x, ed_x) == 1) return PFF(st_x, ed_x);           // 如果到达该位移已经超过道路范围，则全程超速
    if (fcmp(st_x + spd_x, ed_x) == 0) return PFF(st_x, ed_x - MARGIN);  // 如果到达末端时恰好不再超速，则除结束点外全程超速
    return PFF(st_x, st_x + spd_x - MARGIN);                             // 否则在达到该位移前全程超速
  }
}

void solve() {
  std::cin >> N >> M >> L >> V;
  std::vector<PFF> spd(N + 1);

  for (int i = 1, d, v, a; i <= N; ++i) {
    std::cin >> d >> v >> a;
    spd[i] = get_speeding_interval(d, v, a);  // 获取每辆车的超速区间
  }

  std::vector<int> p(M + 1);
  for (int i = 1; i <= M; ++i) std::cin >> p[i];

  auto bin_geq = [&](f64 x) -> int {
    int l = 1, r = M + 1;
    while (l < r) {
      int mid = (l + r) >> 1;
      if (fcmp(p[mid], x) != -1) r = mid;
      else l = mid + 1;
    }
    return r;
  };

  auto bin_leq = [&](f64 x) -> int {
    int l = 0, r = M;
    while (l < r) {
      int mid = (l + r + 1) >> 1;
      if (fcmp(p[mid], x) != 1) l = mid;
      else r = mid - 1;
    }
    return l;
  };

  int ans1 = 0;
  std::vector<PII> seg;

  for (int i = 1; i <= N; ++i) {
    if (spd[i].first < 0 && spd[i].second < 0) continue;
    int l = bin_geq(spd[i].first);
    int r = bin_leq(spd[i].second);
    if (l <= r) ++ans1, seg.emplace_back(l, r);  // 将超速区间转化为测速仪数组上的线段
  }

  std::sort(seg.begin(), seg.end(), [](const PII& x, const PII& y) {
    if (x.first ^ y.first) return x.first < y.first;  // 左端点从小到大
    return x.second > y.second;                       // 右端点从大到小
  });

  std::vector<bool> flag(seg.size());
  int min_r = std::numeric_limits<int>::max();

  for (size_t i = seg.size() - 1; ~i; --i)       // 显然，完全包含其他线段的线段可以不用考虑
    if (min_r <= seg[i].second) flag[i] = true;  // 如果有右端点更小的区间，则当前区间可以不考虑
    else min_r = seg[i].second;                  // 否则更新最小右端点

  int ans2 = 0, cov_r = 0;

  for (size_t i = 0; i < seg.size(); ++i)
    if (!flag[i] && seg[i].first > cov_r)  // 如果当前线段没有被删掉，且左端点没有被覆盖
      ++ans2, cov_r = seg[i].second;       // 则添加一个测速仪，并更新被覆盖区间的右端点

  std::cout << ans1 << ' ';
  std::cout << M - ans2 << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) solve();

  std::cout.flush();
  return 0;
}
