#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;

const int N = 2e5 + 5;

int n, m;

struct SegTree {
  struct Node {
    int l, r, len;
    int sum, tag;
    int lmax, rmax, mmax;
  } node[N << 2];

  void pushup(int u) {
    Node &rt = node[u];
    Node lc = node[u << 1];
    Node rc = node[u << 1 | 1];

    rt.sum = lc.sum + rc.sum;
    rt.lmax = (lc.lmax != lc.len ? lc.lmax : lc.len + rc.lmax);
    rt.rmax = (rc.rmax != rc.len ? rc.rmax : lc.rmax + rc.len);
    rt.mmax = max({lc.mmax, rc.mmax, lc.rmax + rc.lmax});
  }

  void pushdown(int u) {
    Node &rt = node[u];
    Node &lc = node[u << 1];
    Node &rc = node[u << 1 | 1];

    if (rt.tag != -1) {
      lc.tag = rc.tag = rt.tag;
      lc.sum = rt.tag * lc.len;
      rc.sum = rt.tag * rc.len;
      lc.lmax = lc.rmax = lc.mmax = !rt.tag * lc.len;
      rc.lmax = rc.rmax = rc.mmax = !rt.tag * rc.len;
      rt.tag = -1;
    }
  }

  void build(int l = 1, int r = n, int u = 1) {
    node[u].l = l;
    node[u].r = r;
    node[u].tag = -1;
    node[u].len = r - l + 1;

    if (l == r) {
      node[u].sum = 1;  // 初始时全部为脑组织
      node[u].lmax = node[u].rmax = node[u].mmax = 0;
      return;
    }

    int mid = (l + r) >> 1;

    build(l, mid, u << 1);
    build(mid + 1, r, u << 1 | 1);

    pushup(u);
  }

  // 区间修改
  void range_assign(int l, int r, bool value = 0, int u = 1) {
    if (node[u].l >= l && node[u].r <= r) {
      node[u].tag = value;
      node[u].sum = value * node[u].len;
      node[u].lmax = node[u].rmax = node[u].mmax = !value * node[u].len;
      return;
    }

    pushdown(u);

    int mid = (node[u].l + node[u].r) >> 1;

    if (l <= mid) range_assign(l, r, value, u << 1);
    if (r > mid) range_assign(l, r, value, u << 1 | 1);

    pushup(u);
  }

  // 求区间和，即求区间内脑组织的总数
  int query_range_sum(int l, int r, int u = 1) {
    if (node[u].l >= l && node[u].r <= r)
      return node[u].sum;

    pushdown(u);

    int mid = (node[u].l + node[u].r) >> 1;
    int ret = 0;

    if (l <= mid) ret += query_range_sum(l, r, u << 1);
    if (r > mid) ret += query_range_sum(l, r, u << 1 | 1);

    return ret;
  }

  // 区间填零，即使用 left 个脑组织在区间上修补脑洞，返回修补完后剩下的脑组织数量
  int range_fill(int l, int r, int left, int u = 1) {
    if (left == 0) return 0;

    // 已经定位到当前区间并且剩下的脑组织总数足以填入区间内的所有脑洞
    if (node[u].l >= l && node[u].r <= r && node[u].len - node[u].sum <= left) {
      int tmp = node[u].len - node[u].sum;  // 保存脑洞的数量
      node[u].tag = 1;                      // 将该区间修改为 1
      node[u].sum = node[u].len;
      node[u].lmax = node[u].rmax = node[u].mmax = 0;
      return left - tmp;  // 返回剩下的脑组织数量
    }

    pushdown(u);

    int ret = 0;
    if (node[u << 1].r < l)                      // 如果当前区间左子区间的右端点在起点的左边
      ret = range_fill(l, r, left, u << 1 | 1);  // 就从右子区间开始填
    else if (node[u << 1 | 1].l > r)             // 如果当前区间右子区间的左端点在终点的右边
      ret = range_fill(l, r, left, u << 1);      // 就从左子区间开始填
    else                                         // 否则先填左边再填右边
      ret = range_fill(l, r, range_fill(l, r, left, u << 1), u << 1 | 1);

    pushup(u);

    return ret;
  }

  // 询问区间内最长脑洞的长度
  int query_max_zero_length(int l, int r, int u = 1) {
    if (node[u].l >= l && node[u].r <= r)
      return node[u].mmax;

    pushdown(u);

    if (node[u << 1].r < l)  // 同上
      return query_max_zero_length(l, r, u << 1 | 1);
    if (node[u << 1 | 1].l > r)
      return query_max_zero_length(l, r, u << 1);

    return max({query_max_zero_length(l, r, u << 1),    // 左子区间的最长脑洞
      query_max_zero_length(l, r, u << 1 | 1),          // 右子区间的最长脑洞
      min(node[u << 1].rmax, node[u << 1 | 1].l - l) +  // 跨左右区间范围内的最长脑洞
        min(node[u << 1 | 1].lmax, r - node[u << 1].r)});
  }
} SGT;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;

  SGT.build();

  while (m--) {
    int type, l1, r1, l2, r2;
    cin >> type >> l1 >> r1;

    if (type == 0)
      SGT.range_assign(l1, r1);
    else if (type == 2)
      cout << SGT.query_max_zero_length(l1, r1) << endl;
    else {
      cin >> l2 >> r2;
      int tissue = SGT.query_range_sum(l1, r1);  // 获取 [l1, r1] 内可用脑组织的数量
      SGT.range_assign(l1, r1);                  // 将 [l1, r1] 区间覆盖为 0
      SGT.range_fill(l2, r2, tissue);            // 将脑组织填充到脑洞里
    }
  }

  return fflush(stdout), 0;
}
