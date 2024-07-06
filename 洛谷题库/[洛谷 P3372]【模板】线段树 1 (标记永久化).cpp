#include <iostream>

namespace FastIO {
  const int MAX_BUF = 1 << 16;
  char buf[MAX_BUF], *p1, *p2;
  char pbuf[MAX_BUF], *pp = pbuf;

  char getchar() { return (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAX_BUF, stdin), p1 == p2) ? EOF : *p1++); }
  void putchar(char c) { (((pp - pbuf == MAX_BUF) && (fwrite(pbuf, 1, MAX_BUF, stdout), pp = pbuf)), *pp++ = c); }
  void flush() { (pp - pbuf) && fwrite(pbuf, 1, pp - pbuf, stdout); }

  template <typename T = int>
  T read() {
    short int f = 1;
    T var = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
      if (ch == '-') f = -f;
      ch = getchar();
    }
    while (ch >= '0' && ch <= '9') var = var * 10 + ch - '0', ch = getchar();
    return var * f;
  }

  template <typename T>
  void write(T x) {
    static int stack[40];
    if (x < 0) putchar('-'), x = -x;
    int top = 0;
    do stack[top++] = x % 10, x /= 10;
    while (x);
    while (top) putchar(stack[--top] + 48);
  }
}  // namespace FastIO
using namespace FastIO;

using LL = long long;

const int MAX_N = 1e5 + 5;

int N;

struct SegT {
  LL sum[MAX_N << 2], tag[MAX_N << 2];

  void pull(int u) { sum[u] = sum[u << 1] + sum[u << 1 | 1]; }

  void init(int u = 1, int nl = 1, int nr = N) {
    if (nl == nr) return sum[u] = read(), void();
    int mid = (nl + nr) >> 1;
    init(u << 1, nl, mid);
    init(u << 1 | 1, mid + 1, nr);
    pull(u);
  }

  void upd(int l, int r, LL v, int u = 1, int nl = 1, int nr = N) {
    sum[u] += (r - l + 1LL) * v;
    if (l == nl && r == nr) return tag[u] += v, void();
    int mid = (nl + nr) >> 1;
    if (r <= mid) return upd(l, r, v, u << 1, nl, mid);
    if (l > mid) return upd(l, r, v, u << 1 | 1, mid + 1, nr);
    return upd(l, mid, v, u << 1, nl, mid), upd(mid + 1, r, v, u << 1 | 1, mid + 1, nr);
  }

  LL qry(int l, int r, int u = 1, int nl = 1, int nr = N, LL tags = 0) {
    if (l == nl && r == nr) return sum[u] + (r - l + 1LL) * tags;
    int mid = (nl + nr) >> 1;
    if (r <= mid) return qry(l, r, u << 1, nl, mid, tags + tag[u]);
    if (l > mid) return qry(l, r, u << 1 | 1, mid + 1, nr, tags + tag[u]);
    return qry(l, mid, u << 1, nl, mid, tags + tag[u]) + qry(mid + 1, r, u << 1 | 1, mid + 1, nr, tags + tag[u]);
  }
} T;

int main() {
  N = read();
  int q = read();

  T.init();

  while (q--) {
    static int type, x, y, k;
    type = read(), x = read(), y = read();

    if (type == 1) {
      k = read<LL>();
      T.upd(x, y, k);
    } else
      write(T.qry(x, y)), putchar('\n');
  }

  return flush(), 0;
}
