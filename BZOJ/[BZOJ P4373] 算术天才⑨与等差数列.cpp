#include <set>
#include <vector>
#include <numeric>
#include <iostream>
#include <unordered_map>

using LL = long long;

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

  void swrite(const std::string s) {
    for (char ch : s)
      putchar(ch);
  }
}  // namespace FastIO
using namespace FastIO;

const int MAX_N = 3e5 + 5;

int N, q;
int a[MAX_N], pv[MAX_N];

std::unordered_map<int, std::set<int>> map;

struct SegT {
  struct Node {
    int max, min;
    int lmost, rmost;
    int gcd, max_pre;

    void set(int x) { max = min = lmost = rmost = x; }
  } tr[MAX_N << 2];

#define L(u) ((u) << 1)
#define R(u) ((u) << 1 | 1)

  Node merge(Node lc, Node rc) {
    static Node ret;
    ret.max = std::max(lc.max, rc.max);
    ret.min = std::min(lc.min, rc.min);
    ret.lmost = lc.lmost, ret.rmost = rc.rmost;
    ret.max_pre = std::max(lc.max_pre, rc.max_pre);
    ret.gcd = std::gcd(std::gcd(lc.gcd, rc.gcd), abs(lc.rmost - rc.lmost));
    return ret;
  }

  void init(int u = 1, int nl = 1, int nr = N) {
    if (nl == nr) {
      tr[u].gcd = 0;
      tr[u].set(a[nl] = read<int>());
      tr[u].max_pre = pv[nl] = map[a[nl]].empty() ? -1 : *map[a[nl]].rbegin();
      map[a[nl]].insert(nl);
      return;
    }
    int mid = (nl + nr) >> 1;
    init(L(u), nl, mid);
    init(R(u), mid + 1, nr);
    tr[u] = merge(tr[L(u)], tr[R(u)]);
  }

  void upd(int x, int v, int u = 1, int nl = 1, int nr = N) {
    if (nl == nr) {
      tr[u].set(a[x] = v);
      tr[u].max_pre = pv[x];
      return;
    }
    int mid = (nl + nr) >> 1;
    if (x <= mid) upd(x, v, L(u), nl, mid);
    else upd(x, v, R(u), mid + 1, nr);
    tr[u] = merge(tr[L(u)], tr[R(u)]);
  }

  Node qry(int l, int r, int u = 1, int nl = 1, int nr = N) {
    if (nl >= l && nr <= r) return tr[u];
    int mid = (nl + nr) >> 1;
    if (l > mid) return qry(l, r, R(u), mid + 1, nr);
    if (r <= mid) return qry(l, r, L(u), nl, mid);
    return merge(qry(l, r, L(u), nl, mid), qry(l, r, R(u), mid + 1, nr));
  }

#undef L
#undef R
} T;

int main() {
  N = read<int>();
  q = read<int>();

  T.init();

  while (q--) {
    static int type, x, y, k;
    static int key = 0;

    type = read<int>();
    x = read<int>() ^ key;
    y = read<int>() ^ key;
    (type == 2) && (k = read<int>() ^ key);

    // 修改操作
    if (type == 1) {
      static std::set<int>::iterator iter;

      // 更新受到影响的原后继
      iter = map[a[x]].find(x);                     // 找到原本 x 在 a[x] 下标桶里的位置
      if (++iter != map[a[x]].end())                // 如果 x 在桶中具有后继
        pv[*iter] = pv[x], T.upd(*iter, a[*iter]);  // 将后继的前驱从 x 更新为 x 的前驱
      map[a[x]].erase(x), a[x] = y;                 // 从桶中删除 x 并更新实际值

      // 更新受到影响的新后继
      iter = map[a[x]].lower_bound(x);                     // 找到 x 在 y 下标桶里待加入位置的后继
      if (iter != map[a[x]].end())                         // 如果待加入位置存在后继
        pv[*iter] = x, T.upd(*iter, a[*iter]);             // 将后继的前驱更新为 x
      pv[x] = iter == map[a[x]].begin() ? -1 : *(--iter);  // 如果待加入位置存在前驱就更新 x 的前驱

      // 将 x 实际插入 y 下标桶中并更新线段树的对应位置
      map[a[x]].insert(x);
      T.upd(x, a[x]);
    }

    // 查询操作
    else {
      if (x == y) {  // 如果查询范围长度为 1，则特判
        swrite("Yes\n"), ++key;
        continue;
      }

      static bool flag;
      flag = true;

      SegT::Node ret = T.qry(x, y);

      if (ret.max - ret.min != (LL)(y - x) * k) flag = false;  // 等差数列的极差应该等于相邻项的公差之和
      if (k != 0 && ret.max_pre >= x) flag = false;            // 如果公差不为 0，则等差数列内不能出现重复元素
      if (ret.gcd != k) flag = false;                          // 相邻两项的公差应等于任意两数之差的绝对值的最大公因数

      swrite(flag ? "Yes\n" : "No\n"), key += flag;
    }
  }

  return flush(), 0;
}
