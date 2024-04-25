#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")

#include <numeric>
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

using l64 = long long int;

const int MAX_N = 2e6 + 5;

int n;
int p[MAX_N], d[MAX_N];
l64 fuel[MAX_N], sum_f[MAX_N];

int q[MAX_N];

bool ans[MAX_N];

int main() {
  n = read<int>();

  // 逆时针行进
  for (int i = 1; i <= n; ++i) {
    p[i] = p[i + n] = read<int>();
    d[i] = d[i + n] = read<int>();
    fuel[i] = fuel[i + n] = p[i] - d[i];
  }

  std::partial_sum(fuel + 1, fuel + n * 2 + 1, sum_f + 1);

  for (int i = n * 2, qh = 0, qr = -1; i; --i) {
    if (qh <= qr && q[qh] >= i + n) ++qh;
    while (qh <= qr && sum_f[q[qr]] >= sum_f[i]) --qr;
    q[++qr] = i;
    if (i <= n && sum_f[q[qh]] >= sum_f[i - 1]) ans[i] = true;
  }

  // 顺时针行进
  d[0] = d[n];

  for (int i = 1; i <= n; ++i)
    fuel[i] = fuel[i + n] = p[i] - d[i - 1];

  std::partial_sum(fuel + 1, fuel + n * 2 + 1, sum_f + 1);

  for (int i = 1, qh = 0, qr = -1; i <= n * 2; ++i) {
    if (qh <= qr && q[qh] < i - n) ++qh;
    if (i > n && sum_f[i] >= sum_f[q[qh]]) ans[i - n] = true;
    while (qh <= qr && sum_f[q[qr]] <= sum_f[i]) --qr;
    q[++qr] = i;
  }

  for (int i = 1; i <= n; ++i)
    if (ans[i]) putchar('T'), putchar('A'), putchar('K'), putchar('\n');
    else putchar('N'), putchar('I'), putchar('E'), putchar('\n');

  return fflush(stdout), 0;
}
