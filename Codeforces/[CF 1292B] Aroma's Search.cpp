#include <bits/stdc++.h>

#define x first
#define y second

using i64 = long long;
using i128 = __int128;
using PII = std::pair<i64, i64>;

const i64 MAX_N = 1e18;

int ax, ay;
i64 bx, by;
std::vector<PII> p;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  p.emplace_back();
  std::cin >> p[0].x >> p[0].y >> ax >> ay >> bx >> by;

  while (true) {
    i128 nextPx = (i128)p.back().x * ax + bx;
    i128 nextPy = (i128)p.back().y * ay + by;
    if (nextPx > MAX_N || nextPy > MAX_N) break;
    p.emplace_back(nextPx, nextPy);
  }

  i64 sx, sy, T;
  std::cin >> sx >> sy >> T;

  int ans = 0;
  auto dist = [](i64 x1, i64 y1, i64 x2, i64 y2) { return abs(x1 - x2) + abs(y1 - y2); };

  for (size_t st = 0; st < p.size(); ++st) {
    int cnt = 0;
    i64 t = T, xx = sx, yy = sy;

    for (int i = st; ~i; --i) {
      i64 d = dist(xx, yy, p[i].x, p[i].y);
      if (t >= d) t -= d, xx = p[i].x, yy = p[i].y, ++cnt;
      else break;
    }

    for (size_t i = st + 1; i < p.size(); ++i) {
      i64 d = dist(xx, yy, p[i].x, p[i].y);
      if (t >= d) t -= d, xx = p[i].x, yy = p[i].y, ++cnt;
      else break;
    }

    ans = std::max(ans, cnt);
  }

  std::cout << ans << std::flush;
  return 0;
}
