#include <cstdio>

using i64 = long long;

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

const int MAX_N = 1e6 + 5;

int N, Q;

struct FENWICK {
  i64 data[MAX_N];

  void upd(int i, const i64 delta) {
    for (; i <= N; i += (i & -i))
      data[i] += delta;
  }

  i64 sum(int i) {
    i64 ret = 0;
    for (; i; i -= (i & -i))
      ret += data[i];
    return ret;
  }
} BIT[2];

int main() {
  N = read<int>(), Q = read<int>();
  for (int i = 1, p = 0, c = 0; i <= N; ++i) {
    BIT[0].upd(i, (c = read<int>()) - p);
    BIT[1].upd(i, (c - p) * 1LL * i), p = c;
  }

  auto calc = [&](const int x) -> i64 {
    return BIT[0].sum(x) * (x + 1) - BIT[1].sum(x);
  };

  int t, l, r, x;
  do {
    t = read<int>(), l = read<int>(), r = read<int>();
    if (t == 1) {
      x = read<int>();
      BIT[0].upd(l, x), BIT[0].upd(r + 1, -x);
      BIT[1].upd(l, l * 1LL * x), BIT[1].upd(r + 1, (r + 1LL) * -x);
    } else
      write<i64>(calc(r) - calc(l - 1)), putchar('\n');
  } while (--Q);

  return fflush(stdout), 0;
}
