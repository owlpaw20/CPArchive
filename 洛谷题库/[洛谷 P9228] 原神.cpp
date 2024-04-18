#include <iostream>
#include <algorithm>

#define endl '\n'

namespace FastIO {
  const int MAX_BUF = 1 << 20;
  char buf[MAX_BUF], *p1, *p2;

#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++)

  template <typename T>
  T read() {
    T x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
      if (ch == '-') f = -f;
      ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
      x = x * 10 + ch - 48, ch = getchar();
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

using u32 = unsigned int;
using u64 = unsigned long long int;

const int MAX_N = 1e6 + 5;

int n, m;
u32 a[MAX_N], b[MAX_N], K;

int main() {
  n = read<int>(), m = read<int>(), K = read<int>();
  for (int i = 1; i <= n; ++i) a[i] = read<u32>();
  for (int i = 1; i <= m; ++i) b[i] = read<u32>();

  std::sort(a + 1, a + n + 1, [](const int x, const int y) -> bool { return x > y; });
  std::sort(b + 1, b + m + 1, [](const int x, const int y) -> bool { return x > y; });

  int lmt = std::min(n, m), end = std::max(n, m);
  u64 ans = 0;

  for (int i = 1; i <= lmt; ++i) ans += std::max(a[i] + b[i] + K, a[i] + a[i] + b[i]);
  for (int i = lmt + 1; i <= end; ++i) ans += a[i] + b[i];

  write(ans), putchar('\n');
  fflush(stdout);
  return 0;
}
