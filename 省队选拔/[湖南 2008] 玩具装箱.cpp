#include <iostream>

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
using i128 = __int128_t;

const int MAX_N = 5e4 + 5;

int n, L;
i64 sum_c[MAX_N];
i64 a[MAX_N];   // 将 sum_c[i] + i 合并同类项为 a[i]
i128 b[MAX_N];  // 令 (a[i] + L + 1)^2 为 b[i]

i128 f[MAX_N];
int q[MAX_N];

int main() {
  n = read<int>(), L = read<int>();

  for (int i = 1; i <= n; ++i) {
    sum_c[i] = sum_c[i - 1] + read<int>();
    a[i] = sum_c[i] + i;
    b[i] = i128(a[i] + L + 1) * (a[i] + L + 1);
  }

  b[0] = i64(L + 1) * (L + 1);  // 记得赋初值

  int qh = 0, qr = 0;

  // 斜率为 delta_f + delta_b / delta_a
  // 推导式子可知当队首斜率小于 2 * a[i] 时，队首斜率不再有用

  auto eliminate_front = [&](const int i) -> bool {
    const int h = q[qh], hx = q[qh + 1];
    return f[hx] + b[hx] - f[h] - b[h] <= i128(a[hx] - a[h]) * a[i] * 2;
  };

  auto eliminate_back = [&](const int i) -> bool {
    const int r = q[qr], rp = q[qr - 1];
    return (f[r] + b[r] - f[rp] - b[rp]) * (a[i] - a[rp]) >= (f[i] + b[i] - f[rp] - b[rp]) * (a[r] - a[rp]);
  };

  for (int i = 1; i <= n; ++i) {
    while (qh < qr && eliminate_front(i)) ++qh;
    f[i] = f[q[qh]] + (i128(a[i] - a[q[qh]] - L - 1) * (a[i] - a[q[qh]] - L - 1));
    while (qh < qr && eliminate_back(i)) --qr;
    q[++qr] = i;
  }

  write(f[n]), putchar('\n');
  return fflush(stdout), 0;
}
