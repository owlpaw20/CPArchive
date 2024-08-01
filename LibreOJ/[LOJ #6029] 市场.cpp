#include <bits/stdc++.h>

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

int N, q;
int a[MAX_N];

LL fdiv(LL x, LL y) { return floor(x * 1.0 / y); }

struct SegT {
  struct Node {
    int len;
    LL min, max, sum;
    LL tag;

    Node operator+(const Node &x) const {
      return {
        len + x.len,
        std::min(min, x.min),
        std::max(max, x.max),
        sum + x.sum,
        0,
      };
    }

    void modify(int t) {
      min += t, max += t;
      sum += t * len;
      tag += t;
    }
  } tr[MAX_N << 2];

  void push(int u) {
    if (tr[u].tag == std::numeric_limits<LL>::min()) return;
    tr[u << 1].modify(tr[u].tag);
    tr[u << 1 | 1].modify(tr[u].tag);
    tr[u].tag = 0;
  }

  void init(int u = 1, int nl = 1, int nr = N) {
    if (nl == nr) return tr[u] = {1, a[nl] = read(), a[nl], a[nl], std::numeric_limits<LL>::min()}, void();
    int mid = (nl + nr) >> 1;
    init(u << 1, nl, mid);
    init(u << 1 | 1, mid + 1, nr);
    tr[u] = tr[u << 1] + tr[u << 1 | 1];
  }

  void range_add(int l, int r, int v, int u = 1, int nl = 1, int nr = N) {
    if (nl >= l && nr <= r) return tr[u].modify(v);
    push(u);
    int mid = (nl + nr) >> 1;
    if (l <= mid) range_add(l, r, v, u << 1, nl, mid);
    if (r > mid) range_add(l, r, v, u << 1 | 1, mid + 1, nr);
    tr[u] = tr[u << 1] + tr[u << 1 | 1];
  }

  void range_div(int l, int r, int d, int u = 1, int nl = 1, int nr = N) {
    if (nl >= l && nr <= r)
      if (tr[u].max - tr[u].min == fdiv(tr[u].max, d) - fdiv(tr[u].min, d))
        return tr[u].modify(fdiv(tr[u].max, d) - tr[u].max);
    push(u);
    int mid = (nl + nr) >> 1;
    if (l <= mid) range_div(l, r, d, u << 1, nl, mid);
    if (r > mid) range_div(l, r, d, u << 1 | 1, mid + 1, nr);
    tr[u] = tr[u << 1] + tr[u << 1 | 1];
  }

  Node qry(int l, int r, int u = 1, int nl = 1, int nr = N) {
    if (nl >= l && nr <= r) return tr[u];
    push(u);
    int mid = (nl + nr) >> 1;
    if (r <= mid) return qry(l, r, u << 1, nl, mid);
    if (l > mid) return qry(l, r, u << 1 | 1, mid + 1, nr);
    return qry(l, r, u << 1, nl, mid) + qry(l, r, u << 1 | 1, mid + 1, nr);
  }
} T;

int main() {
  N = read(), q = read();

  T.init();

  while (q--) {
    static int type, l, r;

    type = read();
    l = read() + 1;
    r = read() + 1;

    switch (type) {
      case 1:
        T.range_add(l, r, read());
        break;

      case 2:
        T.range_div(l, r, read());
        break;

      case 3:
        write(T.qry(l, r).min), putchar('\n');
        break;

      case 4:
        write(T.qry(l, r).sum), putchar('\n');
        break;
    }
  }

  flush();
  return 0;
}
