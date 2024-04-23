#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")

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

const int MAX_N = 1e3 + 5;
const int INF = 2e9;

int n, m, s;
int o[MAX_N][MAX_N], q[MAX_N];
int row_min[MAX_N][MAX_N], row_max[MAX_N][MAX_N];

int a[MAX_N], b[MAX_N], c[MAX_N];

template <class Comp>
void get(int a[], int f[], int len, Comp cmp) {
  for (int i = 1, qh = 0, qr = -1; i <= len; ++i) {
    while (qh <= qr && q[qh] < i - s + 1) ++qh;
    while (qh <= qr && !cmp(a[q[qr]], a[i])) --qr;
    q[++qr] = i;
    f[i] = a[q[qh]];
  }
}

int main() {
  n = read<int>();
  m = read<int>();
  s = read<int>();

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j)
      o[i][j] = read<int>();
    get(o[i], row_min[i], m, std::less<int>());
    get(o[i], row_max[i], m, std::greater<int>());
  }

  int ans = INF;

  for (int i = s; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) a[j] = row_min[j][i];
    get(a, b, n, std::less<int>());

    for (int j = 1; j <= n; ++j) a[j] = row_max[j][i];
    get(a, c, n, std::greater<int>());

    for (int j = s; j <= n; ++j)
      ans = std::min(ans, c[j] - b[j]);
  }

  write(ans), putchar('\n');
  return fflush(stdout), 0;
}
