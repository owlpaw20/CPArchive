#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <numeric>
#include <iostream>
#include <algorithm>

#ifdef _WIN32
#define getchar _getchar_nolock
#define putchar _putchar_nolock
#endif

#ifdef unix
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif

namespace FastIO {
  template <typename T>
  inline T read() {
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
  inline void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
  }
}  // namespace FastIO
using namespace FastIO;

#define endl '\n'

using f64 = double;
using l64 = long long int;

const int MAX_N = 1e5 + 5;
const int MAX_P = 1e2 + 5;
const l64 INF = 9e18;

int n, m, p;
int d[MAX_N];
l64 t[MAX_N], sum_t[MAX_N];

int q[MAX_N];
l64 f[2][MAX_N];  // 已经派出 i 名饲养员，接走了前 j 只猫的最小时间（可以将 i 这一维滚动掉）

// 转移方程及其推导可以见 https://www.acwing.com/solution/content/68473/

int main() {
  n = read<int>(), m = read<int>(), p = read<int>();
  for (int i = 2; i <= n; ++i) d[i] = read<int>() + d[i - 1];
  for (int i = 1, h; i <= m; ++i) h = read<int>(), t[i] = read<int>() - d[h];

  std::sort(t + 1, t + m + 1);
  std::partial_sum(t + 1, t + m + 1, sum_t + 1);

  auto slope = [&](const int i, const int j1, const int j2) -> f64 {
    return (f[!i][j1] - f[!i][j2] + sum_t[j1] - sum_t[j2]) * 1.0 / (j1 - j2);
  };

  f[0][0] = f[1][0] = 0;
  for (int j = 1; j <= m; ++j) f[0][j] = f[1][j] = INF;

  bool cur = 0;
  for (int i = 1; i <= p; ++i, cur = !cur) {
    for (int j = 1, qh = 0, qr = 0; j <= m; ++j) {
      while (qh < qr && slope(cur, q[qh + 1], q[qh]) <= t[j]) ++qh;
      f[cur][j] = f[!cur][q[qh]] - t[j] * q[qh] + sum_t[q[qh]] + t[j] * j - sum_t[j];
      while (qh < qr && slope(cur, q[qr], q[qr - 1]) >= slope(cur, j, q[qr])) --qr;
      q[++qr] = j;
    }
  }

  write(f[!cur][m]), putchar('\n');
  return fflush(stdout), 0;
}
