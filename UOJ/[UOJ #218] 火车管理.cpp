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

const int MAX_N = 5e5 + 5;

int N;

struct PerSegT {
  struct Node {
    int l, r;
    int val;
  } tr[MAX_N << 6];

  int size;
  int root[MAX_N << 1];

  int _upd(int l, int r, int val, int u, int nl = 1, int nr = N) {
    int v = ++size;
    tr[v] = tr[u];
    if (nl >= l && nr <= r) return tr[v].val = val, tr[v].l = tr[v].r = 0, v;
    int mid = (nl + nr) >> 1;
    if (l <= mid) tr[v].l = _upd(l, r, val, tr[u].l, nl, mid);
    if (r > mid) tr[v].r = _upd(l, r, val, tr[u].r, mid + 1, nr);
    return v;
  }

  int _qry(int x, int u, int nl = 1, int nr = N) {
    if (!u) return -1;
    int mid = (nl + nr) >> 1, ret;
    if (x <= mid) ret = _qry(x, tr[u].l, nl, mid);
    else ret = _qry(x, tr[u].r, mid + 1, nr);
    return ret != -1 ? ret : tr[u].val;
  }

  void upd(int t, int l, int r, int val) { root[t] = _upd(l, r, val, root[t]); }
  int qry(int t, int x) { return _qry(x, root[t]); }
  PerSegT() : size(0) { tr[0].val = -1; }
} top, tim;

struct SegT {
  struct Node {
    int len, sum, tag;
  } tr[MAX_N << 2];

#define L(u) ((u) << 1)
#define R(u) ((u) << 1 | 1)

  void push(int u) {
    if (!tr[u].tag) return;
    tr[L(u)].tag = tr[R(u)].tag = tr[u].tag;
    tr[L(u)].sum = tr[u].tag * tr[L(u)].len;
    tr[R(u)].sum = tr[u].tag * tr[R(u)].len;
    tr[u].tag = 0;
  }

  void init(int u = 1, int nl = 1, int nr = N) {
    tr[u].len = nr - nl + 1;
    if (nl == nr) return tr[u].tag = tr[u].sum = 0, void();
    int mid = (nl + nr) >> 1;
    init(L(u), nl, mid), init(R(u), mid + 1, nr);
  }

  void upd(int l, int r, int val, int u = 1, int nl = 1, int nr = N) {
    if (nl >= l && nr <= r) return tr[u].tag = val, tr[u].sum = tr[u].len * val, void();
    push(u);
    int mid = (nl + nr) >> 1;
    if (l <= mid) upd(l, r, val, L(u), nl, mid);
    if (r > mid) upd(l, r, val, R(u), mid + 1, nr);
    tr[u].sum = tr[L(u)].sum + tr[R(u)].sum;
  }

  int qry(int l, int r, int u = 1, int nl = 1, int nr = N) {
    if (nl >= l && nr <= r) return tr[u].sum;
    push(u);
    int mid = (nl + nr) >> 1, ret = 0;
    if (l <= mid) ret += qry(l, r, L(u), nl, mid);
    if (r > mid) ret += qry(l, r, R(u), mid + 1, nr);
    return ret;
  }

#undef L
#undef R
} T;

int main() {
  N = read();
  int q = read();
  int ty = read();

  T.init();

  for (int i = 1; i <= q; ++i) {
    static int type, l, r, x, lastans = 0;
    type = read();

    // 保存当前时刻的两颗主席树的版本
    top.root[i] = top.root[i - 1];
    tim.root[i] = tim.root[i - 1];

    // 查询区间栈顶和
    if (type == 1) {
      l = (read() + lastans * ty) % N + 1;
      r = (read() + lastans * ty) % N + 1;
      if (l > r) std::swap(l, r);
      write(lastans = T.qry(l, r)), putchar('\n');
    }

    // 单点弹栈
    else if (type == 2) {
      l = (read() + lastans * ty) % N + 1;

      int t = tim.qry(i, l);  // 获取被弹出的位置的栈顶元素入栈的时间
      if (t <= 0) continue;  // 如果被弹出的位置的栈不空，则弹出该元素

      // 恢复上一个栈顶的入栈时间
      int v = tim.qry(t - 1, l);  // 获取上一个栈顶元素的入栈时间
      if (v == -1) v = 0;         // 如果弹出当前栈顶之后栈不空
      tim.upd(i, l, l, v);        // 将该栈的栈顶入栈时间进行修改

      // 恢复上一个栈顶的元素值
      v = top.qry(t - 1, l);
      if (v == -1) v = 0;
      top.upd(i, l, l, v);

      // 更新答案线段树上的值
      T.upd(l, l, v);
    }

    // 区间入栈
    else {
      l = (read() + lastans * ty) % N + 1;
      r = (read() + lastans * ty) % N + 1;
      if (l > r) std::swap(l, r);
      x = read();

      T.upd(l, r, x);       // 在答案线段树对应区间进行区间覆盖
      top.upd(i, l, r, x);  // 在入栈时间的主席树对应区间进行区间覆盖
      tim.upd(i, l, r, i);  // 在栈顶元素的主席树对应区间进行区间覆盖
    }
  }

  return flush(), 0;
}
