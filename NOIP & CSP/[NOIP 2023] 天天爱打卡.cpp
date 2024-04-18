#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

#define endl '\n'

namespace FastIO {
  const int MAX_BUF = 1 << 20;
  char buf[MAX_BUF], *p1, *p2;

#define getchar() \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++)

  template <typename T>
  T read() {
    T x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
      if (ch == '-') f = -f;
      ch = getchar();
    }
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - 48, ch = getchar();
    return x * f;
  }

  template <typename T>
  void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
  }
}  // namespace FastIO
using namespace FastIO;

using i64 = long long int;
using c64 = const long long int;
using cu32 = const unsigned long int;

const int MAX_M = 1e5 + 5;
const int MAX_LEN = 2e5 + 5;

/*
  f[i] 表示第 i 填不打卡时的最大能量，令 j 为上一次不打卡的日期，则有：
  f[i] = f[j] + w(j + 1, i - 1) - (i - j - 1) * d
  将需要查询的 j + 1 和 i - 1 离散化
  线段树维护 f[i] + i * d 的区间最大值
*/

int N, M, K, D, len;
int lb[MAX_M], rb[MAX_M], val[MAX_M];
int disc[MAX_LEN], idx;

std::vector<std::vector<int>> qr;

// 维护单点、区间加和区间求最大值的线段树
struct SegT {
  i64 max[MAX_LEN << 2];
  i64 tag[MAX_LEN << 2];

  inline void pull(cu32 rt) { max[rt] = std::max(max[rt << 1], max[rt << 1 | 1]); }

  inline void push(cu32 rt) {
    max[rt << 1] += tag[rt];
    tag[rt << 1] += tag[rt];
    max[rt << 1 | 1] += tag[rt];
    tag[rt << 1 | 1] += tag[rt];
    tag[rt] = 0;
  }

  void range_add(cu32 l, cu32 r, c64 v, cu32 u = 1, cu32 nl = 1, cu32 nr = len) {
    if (nl >= l && nr <= r) {
      max[u] += v;
      tag[u] += v;
      return;
    }

    if (tag[u]) push(u);

    cu32 mid = (nl + nr) >> 1;

    if (l <= mid) range_add(l, r, v, u << 1, nl, mid);
    if (r > mid) range_add(l, r, v, u << 1 | 1, mid + 1, nr);

    pull(u);
  }

  i64 query_max(cu32 l, cu32 r, cu32 u = 1, cu32 nl = 1, cu32 nr = len) {
    if (nl >= l && nr <= r) return max[u];

    if (tag[u]) push(u);

    cu32 mid = (nl + nr) >> 1;
    i64 ret = 0;

    if (l <= mid) ret = std::max(ret, query_max(l, r, u << 1, nl, mid));
    if (r > mid) ret = std::max(ret, query_max(l, r, u << 1 | 1, mid + 1, nr));

    return ret;
  }

  void init() {
    memset(max, 0, sizeof max);
    memset(tag, 0, sizeof tag);
  }
} SEGT;

void solve() {
  N = read<int>(), M = read<int>();
  K = read<int>(), D = read<int>();

  idx = 0;  // 重置离散化数组

  for (int i = 1, len; i <= M; ++i) {
    rb[i] = read<int>(), len = read<int>();  // 输入右端点和区间长度
    lb[i] = rb[i] - len + 1;                 // 获取左端点
    val[i] = read<int>();

    // 存储需要离散化的值
    disc[++idx] = lb[i] - 1;
    disc[++idx] = rb[i] + 1;
  }

  // 离散化
  std::sort(disc + 1, disc + idx + 1);
  len = std::unique(disc + 1, disc + idx + 1) - disc - 1;

  for (int i = 1; i <= M; ++i) {
    lb[i] = std::lower_bound(disc + 1, disc + len + 1, lb[i] - 1) - disc;
    rb[i] = std::lower_bound(disc + 1, disc + len + 1, rb[i] + 1) - disc;
  }

  // 存储所有挑战的右端点
  qr.clear(), qr.resize(len + 1, std::vector<int>());
  for (int i = 1; i <= M; ++i) qr[rb[i]].push_back(i);

  SEGT.init();
  disc[0] = 0;

  // 初始化
  SEGT.range_add(1, 1, (i64)disc[1] * D);

  i64 ans = 0;
  int l = 0;

  for (int i = 2; i <= len; ++i) {
    for (int j : qr[i])  // 对当前右端点上的所有挑战进行维护
      SEGT.range_add(1, lb[j], val[j]);

    while (disc[i] - disc[l] - 1 > K) ++l;  // 更新跑步打卡的天数

    // 减去此前的能量值消耗
    ans = std::max(ans, SEGT.query_max(l, i - 1) - (i64)D * (disc[i] - 1));

    // 加上当前的能量值消耗
    SEGT.range_add(i, i, ans + (i64)disc[i] * D);
  }

  std::cout << ans << endl;
}

int main() {
  read<int>();
  int T = read<int>();
  while (T--) solve();

  return fflush(stdout), 0;
}
