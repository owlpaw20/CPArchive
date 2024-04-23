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

const int MAX_N = 1e6 + 5;

int a[MAX_N], q[MAX_N];

int main() {
  int n = read<int>(), K = read<int>();
  for (int i = 1; i <= n; ++i) a[i] = read<int>();

  for (int i = 1, qh = 0, qr = -1; i <= n; ++i) {
    while (qh <= qr && a[q[qr]] >= a[i]) --qr;
    q[++qr] = i;
    if (i >= K) {
      if (q[qh] <= i - K) ++qh;
      write(a[q[qh]]), putchar(' ');
    }
  }

  putchar('\n');

  for (int i = 1, qh = 0, qr = -1; i <= n; ++i) {
    while (qh <= qr && a[q[qr]] <= a[i]) --qr;
    q[++qr] = i;
    if (i >= K) {
      if (q[qh] <= i - K) ++qh;
      write(a[q[qh]]), putchar(' ');
    }
  }

  putchar('\n');
  return fflush(stdout), 0;
}
