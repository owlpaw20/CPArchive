#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")

#include <vector>
#include <iostream>

#define endl '\n'

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

using PII = std::pair<int, int>;

using VI = std::vector<int>;
using VVI = std::vector<VI>;

const int INF = 2e9;

int n, m, s;
VVI a, b, c;

struct SparseTable {
  VVI max, min;
  
  SparseTable() {}
  SparseTable(int n, VI a) {
    int lmt = std::__lg(n) + 1;

    max.resize(n, VI(lmt, -INF));
    min.resize(n, VI(lmt, INF));

    for (int i = 0; i < n; ++i)
      max[i][0] = min[i][0] = a[i];

    for (int j = 1; j < lmt; ++j)
      for (int i = 0; i + (1 << j) - 1 < n; ++i) {
        max[i][j] = std::max(max[i][j - 1], max[i + (1 << (j - 1))][j - 1]);
        min[i][j] = std::min(min[i][j - 1], min[i + (1 << (j - 1))][j - 1]);
      }
  }

  PII query(int l, int r) {
    int t = std::__lg(r - l + 1);
    return PII(std::max(max[l][t], max[r - (1 << t) + 1][t]), std::min(min[l][t], min[r - (1 << t) + 1][t]));
  }

} ST1, ST2;

int main() {
  n = read<int>();
  m = read<int>();
  s = read<int>();

  a.resize(n, VI(m));
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      a[i][j] = read<int>();

  b.resize(m - s + 1, VI(n)), c.resize(m - s + 1, VI(n));
  for (int r = 0; r < n; ++r) {
    ST1 = SparseTable(m, a[r]);
    for (int i = 0, j = s - 1; j < m; ++i, ++j) {
      PII t = ST1.query(i, j);
      b[i][r] = t.first, c[i][r] = t.second;
    }
  }

  int ans = INF;

  for (int r = 0; r + s - 1 < m; ++r) {
    ST1 = SparseTable(n, b[r]), ST2 = SparseTable(n, c[r]);
    for (int i = 0, j = s - 1; j < n; ++i, ++j)
      ans = std::min(ans, ST1.query(i, j).first - ST2.query(i, j).second);
  }

  write(ans), putchar('\n');
  return fflush(stdout), 0;
}
