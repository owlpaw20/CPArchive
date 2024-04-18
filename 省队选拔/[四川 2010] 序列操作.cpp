#include <cstdio>
#include <algorithm>

#define endl '\n'

const int MAX_N = 1e5 + 5;

namespace FastIO {
  const int MAX_BUF = 1 << 20;
  char buf[MAX_BUF], *p1, *p2;

#define getchar() \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++)

  int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
      if (ch == '-') f = -f;
      ch = getchar();
    }
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - 48, ch = getchar();
    return x * f;
  }
  void write(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
  }
}  // namespace FastIO
using namespace FastIO;

struct SegTree {
  struct Node {
    int l, r;
    int cnt0, cnt1;
    int lmax0, lmax1;
    int rmax0, rmax1;
    int mmax0, mmax1;
    int alt, inv;

    void pull(const Node a, const Node b) {
      cnt0 = a.cnt0 + b.cnt0;
      cnt1 = a.cnt1 + b.cnt1;
      lmax0 = (a.cnt1 ? a.lmax0 : a.cnt0 + b.lmax0);
      lmax1 = (a.cnt0 ? a.lmax1 : a.cnt1 + b.lmax1);
      rmax0 = (b.cnt1 ? b.rmax0 : b.cnt0 + a.rmax0);
      rmax1 = (b.cnt0 ? b.rmax1 : b.cnt1 + a.rmax1);
      mmax0 = std::max({a.mmax0, b.mmax0, a.rmax0 + b.lmax0});
      mmax1 = std::max({a.mmax1, b.mmax1, a.rmax1 + b.lmax1});
    }

    void modify(const int type) {
      if (type == 0) {
        alt = inv = 0;
        cnt0 = r - l + 1, cnt1 = 0;
        lmax0 = r - l + 1, lmax1 = 0;
        rmax0 = r - l + 1, rmax1 = 0;
        mmax0 = r - l + 1, mmax1 = 0;
      } else if (type == 1) {
        alt = 1, inv = 0;
        cnt1 = r - l + 1, cnt0 = 0;
        lmax1 = r - l + 1, lmax0 = 0;
        rmax1 = r - l + 1, rmax0 = 0;
        mmax1 = r - l + 1, mmax0 = 0;
      } else {
        inv ^= 1;
        std::swap(cnt0, cnt1);
        std::swap(lmax0, lmax1);
        std::swap(rmax0, rmax1);
        std::swap(mmax0, mmax1);
      }
    }

    void push(Node &a, Node &b) {
      if (alt != -1) a.modify(alt), b.modify(alt), alt = -1;
      if (inv != 0) a.modify(2), b.modify(2), inv = 0;
    }

    Node() {}
    Node(int l, int r) : l(l), r(r), alt(-1), inv(0) {}
    Node(int l, int r, bool x) : l(l), r(r), cnt0(!x), cnt1(x), lmax0(!x), lmax1(x), rmax0(!x), rmax1(x), mmax0(!x),
                                 mmax1(x), alt(-1), inv(0) {}

  } node[MAX_N << 2];

  void build(int l, int r, int u = 1) {
    if (l == r) return (void)(node[u] = Node(l, r, read()));

    node[u] = Node(l, r);

    int mid = (l + r) >> 1;

    build(l, mid, u << 1);
    build(mid + 1, r, u << 1 | 1);

    node[u].pull(node[u << 1], node[u << 1 | 1]);
  }

  void range_overwrite(int l, int r, bool x, int u = 1) {
    if (node[u].l >= l && node[u].r <= r) return node[u].modify(x);

    node[u].push(node[u << 1], node[u << 1 | 1]);

    int mid = (node[u].l + node[u].r) >> 1;

    if (l <= mid) range_overwrite(l, r, x, u << 1);
    if (r > mid) range_overwrite(l, r, x, u << 1 | 1);

    node[u].pull(node[u << 1], node[u << 1 | 1]);
  }

  void range_invert(int l, int r, int u = 1) {
    if (node[u].l >= l && node[u].r <= r) return node[u].modify(2);

    node[u].push(node[u << 1], node[u << 1 | 1]);

    int mid = (node[u].l + node[u].r) >> 1;

    if (l <= mid) range_invert(l, r, u << 1);
    if (r > mid) range_invert(l, r, u << 1 | 1);

    node[u].pull(node[u << 1], node[u << 1 | 1]);
  }

  Node range_query(int l, int r, int u = 1) {
    if (node[u].l >= l && node[u].r <= r) return node[u];

    node[u].push(node[u << 1], node[u << 1 | 1]);

    int mid = (node[u].l + node[u].r) >> 1;
    int flag = 1 * (l <= mid) + 2 * (r > mid);

    if (flag == 1) return range_query(l, r, u << 1);
    if (flag == 2) return range_query(l, r, u << 1 | 1);

    Node ret;
    return ret = Node(),
           ret.pull(
             range_query(l, r, u << 1), range_query(l, r, u << 1 | 1)),
           ret;
  }
} SGT;

int N, M;

int main() {
  int N = read();
  int M = read();

  SGT.build(1, N);

  while (M--) {
    int type = read();
    int l = read() + 1;
    int r = read() + 1;

    if (type == -1)
      continue;
    else if (type == 2)
      SGT.range_invert(l, r);
    else if (type == 0)
      SGT.range_overwrite(l, r, 0);
    else if (type == 1)
      SGT.range_overwrite(l, r, 1);
    else if (type == 3)
      write(SGT.range_query(l, r).cnt1), putchar('\n');
    else if (type == 4)
      write(SGT.range_query(l, r).mmax1), putchar('\n');
  }

  return fflush(stdout), 0;
}
