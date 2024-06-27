#include <iostream>
#include <algorithm>

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
    static int stack[40];
    if (x < 0) putchar('-'), x = -x;
    int top = 0;
    do stack[top++] = x % 10, x /= 10;
    while (x);
    while (top) putchar(stack[--top] + 48);
  }

  std::string sread() {
    std::string var;
    char ch = getchar();
    while (iswspace(ch)) ch = getchar();
    while (!iswspace(ch)) var.push_back(ch), ch = getchar();
    return var;
  }

  void swrite(const std::string s) {
    for (char ch : s)
      putchar(ch);
  }
}  // namespace FastIO
using namespace FastIO;

const int MAX_N = 5e5 + 5;
const int INF = 1e9;

int N;

struct SegT {
  struct Node {
    int sum, max;
    int max_l, max_r;
  } t[MAX_N << 2];

#define L(x) ((x) << 1)
#define R(x) ((x) << 1 | 1)

  Node pull(const Node& lc, const Node& rc) {
    Node ret;
    ret.sum = lc.sum + rc.sum;
    ret.max = std::max({lc.max, rc.max, lc.max_r + rc.max_l});
    ret.max_l = std::max(lc.max_l, lc.sum + rc.max_l);
    ret.max_r = std::max(rc.max_r, rc.sum + lc.max_r);
    return ret;
  }

  void build(int u = 1, int nl = 1, int nr = N) {
    if (nl == nr)
      return t[u].sum = t[u].max = t[u].max_l = t[u].max_r = read<int>(), void();
    int mid = (nl + nr) >> 1;
    build(L(u), nl, mid), build(R(u), mid + 1, nr);
    t[u] = pull(t[L(u)], t[R(u)]);
  }

  void update(int p, int s, int u = 1, int nl = 1, int nr = N) {
    if (nl == nr) return t[u].sum = t[u].max = t[u].max_l = t[u].max_r = s, void();
    int mid = (nl + nr) >> 1;
    if (p <= mid) update(p, s, L(u), nl, mid);
    else update(p, s, R(u), mid + 1, nr);
    t[u] = pull(t[L(u)], t[R(u)]);
  }

  Node query(int l, int r, int u = 1, int nl = 1, int nr = N) {
    if (nl >= l && nr <= r) return t[u];
    int mid = (nl + nr) >> 1;
    if (l <= mid && mid < r)
      return pull(query(l, r, L(u), nl, mid), query(l, r, R(u), mid + 1, nr));
    else if (l <= mid) return query(l, r, L(u), nl, mid);
    else return query(l, r, R(u), mid + 1, nr);
  }

#undef L
#undef R
} T;

int main() {
  N = read<int>();
  int Q = read<int>();

  T.build();

  while (Q--) {
    static int type, x, y;
    type = read<int>(), x = read<int>(), y = read<int>();
    if (type == 1) std::cout << T.query(std::min(x, y), std::max(x, y)).max << '\n';
    else T.update(x, y);
  }

  std::cout.flush();
  return 0;
}
