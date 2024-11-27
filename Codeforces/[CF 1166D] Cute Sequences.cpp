#include <bits/stdc++.h>

namespace FastIO {
  // clang-format off
  const int MAX_BUF = 1 << 16;
  char buf[MAX_BUF], *p1, *p2, pbuf[MAX_BUF], *pp = pbuf;
  char getchar() { return (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAX_BUF, stdin), p1 == p2) ? EOF : *p1++); }
  void putchar(char c) { (((pp - pbuf == MAX_BUF) && (fwrite(pbuf, 1, MAX_BUF, stdout), pp = pbuf)), *pp++ = c); }
  void flush() { (pp - pbuf) && fwrite(pbuf, 1, pp - pbuf, stdout); }
  template <typename T>
  T read() {
    short int f = 1; T var = 0; char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -f; ch = getchar(); }
    while (ch >= '0' && ch <= '9') var = var * 10 + ch - '0', ch = getchar();
    return var * f;
  }
  template <typename T>
  void write(T x) {
    static short int stack[40]; int top = 0;
    if (x < 0) putchar('-'), x = -x;
    do stack[top++] = x % 10, x /= 10; while (x);
    while (top) putchar(stack[--top] + 48);
  }
  // clang-format on
}  // namespace FastIO
using namespace FastIO;

using i64 = long long;
using i128 = __int128_t;

i128 pw2[50];

void solve() {
  i64 a = read<i64>(), b = read<i64>(), m = read<i64>();
  if (a == b) return write(1), putchar(' '), write(a), putchar('\n');

  auto check = [&](int x) -> bool {
    i128 low = pw2[x - 2] * a + 1, high = pw2[x - 2] * a + m;
    for (int i = 2; i < x; ++i) low += pw2[x - i - 1], high += pw2[x - i - 1] * m;
    return low <= b && b <= high;
  };

  for (int x = 2; x <= 50; ++x) {
    if (!check(x)) continue;
    write(x), putchar(' '), write(a);

    i128 rest = b - (a + 1) * pw2[x - 2], sum = a;

    for (int i = 2; i < x; ++i) {
      i128 delta = std::min<i128>(m - 1, rest / pw2[x - i - 1]);
      putchar(' '), write(sum + delta + 1);
      rest -= pw2[x - i - 1] * delta;
      sum += sum, sum += delta + 1;
    }

    putchar(' '), write(b), putchar('\n');
    return;
  }

  write(-1), putchar('\n');
}

int main() {
  pw2[0] = 1;
  for (int i = 1; i < 50; ++i) pw2[i] = pw2[i - 1] << 1;

  int T = read<int>();
  while (T--) solve();

  return flush(), 0;
}
