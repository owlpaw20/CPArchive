#include <bits/stdc++.h>

namespace FastIO {
  const int MAX_BUF = 1 << 16;
  char buf[MAX_BUF], *p1, *p2;
  char pbuf[MAX_BUF], *pp = pbuf;

  char getchar() { return (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAX_BUF, stdin), p1 == p2) ? EOF : *p1++); }
  void putchar(char c) { (((pp - pbuf == MAX_BUF) && (fwrite(pbuf, 1, MAX_BUF, stdout), pp = pbuf)), *pp++ = c); }
  void flush() { (pp - pbuf) && fwrite(pbuf, 1, pp - pbuf, stdout); }

  template <typename T>
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
    static short int stack[40];
    if (x < 0) putchar('-'), x = -x;
    int top = 0;
    do stack[top++] = x % 10, x /= 10;
    while (x);
    while (top) putchar(stack[--top] + 48);
  }
}  // namespace FastIO
using namespace FastIO;

using i64 = long long;
using i128 = __int128;

const int MAX_N = 2e5 + 5;

int N, q, a[MAX_N];
i64 W;

struct SegT {
  struct Node {
    i64 sum, tag;
    int len;
  } tr[MAX_N << 2];

  Node merge(const Node& L, const Node& R) { return {L.sum + R.sum, 0, L.len + R.len}; }

  void modify(int u, i64 tag) {
    tr[u].sum += tag * tr[u].len;
    tr[u].tag += tag;
  }

  void pushup(int u) { tr[u] = merge(tr[u << 1], tr[u << 1 | 1]); }

  void pushdown(int u) {
    if (!tr[u].tag) return;
    modify(u << 1, tr[u].tag);
    modify(u << 1 | 1, tr[u].tag);
    tr[u].tag = 0;
  }

  void build(int u = 1, int nl = 1, int nr = N) {
    tr[u].tag = 0, tr[u].len = nr - nl + 1;
    if (nl == nr) return tr[u].sum = a[nl], void();
    int mid = (nl + nr) >> 1;
    build(u << 1, nl, mid);
    build(u << 1 | 1, mid + 1, nr);
    pushup(u);
  }

  void upd(int l, int r, i64 d, int u = 1, int nl = 1, int nr = N) {
    if (nl >= l && nr <= r) return modify(u, d);
    pushdown(u);
    int mid = (nl + nr) >> 1;
    if (l <= mid) upd(l, r, d, u << 1, nl, mid);
    if (r > mid) upd(l, r, d, u << 1 | 1, mid + 1, nr);
    pushup(u);
  }

  int bin(i64 w, int k, int u = 1, int nl = 1, int nr = N) {
    if (nl == nr) return nl - 1;
    pushdown(u);
    int mid = (nl + nr) >> 1;
    i128 w_cost = tr[u << 1].sum * (1ULL << k);
    if (w - w_cost <= 0) return bin(w, k, u << 1, nl, mid);
    return bin(w - w_cost, k, u << 1 | 1, mid + 1, nr);
  }
} T;

int main() {
  N = read<int>(), q = read<int>(), W = read<i64>();
  for (int i = 1; i <= N; ++i) a[i] = read<int>();

  T.build();

  while (q--) {
    static int l, r, d;
    l = read<int>(), r = read<int>(), d = read<int>();

    T.upd(l, r, d);

    auto get_rounds = [](i64 sum, i64 w) -> int {
      int l = 0, r = 63;
      while (l < r) {
        int mid = (l + r + 1) >> 1;
        if ((i128)sum * ((1ULL << mid) - 1) < w) l = mid;
        else r = mid - 1;
      }
      return l;
    };

    int k = get_rounds(T.tr[1].sum, W);
    int m = T.bin(W - T.tr[1].sum * ((1ULL << k) - 1), k);

    write(k * N + m), putchar('\n');
  }

  return flush(), 0;
}
