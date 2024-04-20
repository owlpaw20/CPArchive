#include <cmath>
#include <iostream>

#define endl '\n'

#ifdef _WIN32
#define getchar_unlocked _getchar_nolock
#define putchar_unlocked _putchar_nolock
#endif

namespace FastIOStr {
  template <typename T>
  T read() {
    T x = 0, f = 1;
    char ch = getchar_unlocked();
    while (ch < '0' || ch > '9') {
      if (ch == '-') f = -f;
      ch = getchar_unlocked();
    }
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - 48, ch = getchar_unlocked();
    return x * f;
  }

  template <typename T>
  void write(T x) {
    if (x < 0) putchar_unlocked('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar_unlocked(x % 10 + '0');
  }
}  // namespace FastIO
using namespace FastIOStr;

using f64 = double;
using c32 = const int;
using PFI = std::pair<f64, int>;

const int MOD_1 = 39989;
const int MOD_2 = 1e9;
const f64 EPS = 1e-10;
const f64 INF = 2e9;
const int MAX_N = 1e5 + 5;
const int MAX_V = MOD_1 + 5;

int idx;

inline int fcmp(const f64 x, const f64 y) {
  if (fabs(x - y) < EPS) return 0;
  return x > y ? 1 : -1;
}

struct Segment {
  f64 k, b;
  int x_l, x_r;

  inline f64 operator()(int x) {
    if (x_l <= x && x <= x_r) return k * x + b;
    return -INF;
  }

} f[MAX_N];

struct LiChaoTree {
  int dom[MAX_V << 2];  // 存储当前区间内最占优势的线段的编号

  PFI max(PFI x, PFI y) {
    if (fabs(x.first - y.first) < EPS) return x.second < y.second ? x : y;
    return x.first < y.first ? y : x;
  }

  // 插入一条编号为 i 的线段
  void insert(int i, c32 l, c32 r, c32 u = 1, c32 nl = 1, c32 nr = MAX_V) {
    if (nl >= l && nr <= r) {
      // 如果当前区间内还没有已经存储的最优线段，则将当前递归的线段视为最优
      if (!dom[u]) return dom[u] = i, void();

      c32 mid = (nl + nr) >> 1;

      // 如果区间中点处，新插入的线段比原有最优线段的 y 值更大，则更新最优线段
      if (fcmp(f[i](mid), f[dom[u]](mid)) == 1) std::swap(i, dom[u]);

      // 以左端点为例，如果左端点处最优线段的 y 值较低
      // 或者最优线段的 y 值相等但编号不是最小的
      // 则说明两线段的交点在左半边区间，递归求解
      if (fcmp(f[i](nl), f[dom[u]](nl)) + (i < dom[u]) > 0) insert(i, l, r, u << 1, nl, mid);
      if (fcmp(f[i](nr), f[dom[u]](nr)) + (i < dom[u]) > 0) insert(i, l, r, u << 1 | 1, mid + 1, nr);

      return;
    }

    c32 mid = (nl + nr) >> 1;

    if (l <= mid) insert(i, l, r, u << 1, nl, mid);
    if (r > mid) insert(i, l, r, u << 1 | 1, mid + 1, nr);
  }

  // 查询横坐标为 x 的直线上纵坐标最大且编号最小的线段编号
  PFI query(c32 x, c32 u = 1, c32 nl = 1, c32 nr = MAX_V) {
    PFI ret = (dom[u] ? PFI(f[dom[u]](x), dom[u]) : PFI(-INF, 0));

    if (nl == nr) return ret;

    int mid = (nl + nr) >> 1;

    if (x <= mid) ret = max(ret, query(x, u << 1, nl, mid));
    else ret = max(ret, query(x, u << 1 | 1, mid + 1, nr));

    return ret;
  }

} LCT;

int main() {
  int n = read<int>();
  int last = 0;

  while (n--) {
    if (read<int>() == 0) {
      int k = (read<int>() + last - 1) % MOD_1 + 1;
      write(last = LCT.query(k).second), putchar_unlocked('\n');
    } else {
      int x_0 = (read<int>() + last - 1) % MOD_1 + 1;
      int y_0 = (read<int>() + last - 1) % MOD_2 + 1;
      int x_1 = (read<int>() + last - 1) % MOD_1 + 1;
      int y_1 = (read<int>() + last - 1) % MOD_2 + 1;

      ++idx;

      if (x_0 == x_1)  // 如果横坐标相等则需要特判，避免除以 0
        f[idx] = {0, (f64)std::max(y_0, y_1), x_0, x_0};
      else {
        f[idx].k = f64(y_1 - y_0) / f64(x_1 - x_0);
        f[idx].b = (f64)y_1 - f[idx].k * x_1;
        f[idx].x_l = std::min(x_0, x_1);
        f[idx].x_r = std::max(x_0, x_1);
      }

      LCT.insert(idx, std::min(x_0, x_1), std::max(x_0, x_1));
    }
  }

  return fflush(stdout), 0;
}
