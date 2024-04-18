#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;

const int N = 5e4 + 5;

struct SegTree {
  struct Node {
    int l, r;
    int lmax, rmax, mmax, sum;
  } node[N << 2];

  void maintain(int u) {
    Node &root = node[u];
    Node &left = node[u << 1];
    Node &right = node[u << 1 | 1];

    root.sum = left.sum + right.sum;
    root.lmax = max(left.lmax, left.sum + right.lmax);
    root.rmax = max(right.rmax, right.sum + left.rmax);
    root.mmax = max({left.mmax, right.mmax, left.rmax + right.lmax});
  }

  void build(int u, int l, int r) {
    node[u].l = l;
    node[u].r = r;

    if (l == r) {
      int x;
      cin >> x;
      node[u].lmax = node[u].rmax = node[u].mmax = node[u].sum = x;
      return;
    }

    int mid = (l + r) >> 1;

    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);

    maintain(u);
  }

  Node query_max_subarray_sum(int u, int l, int r) {
    int nl = node[u].l, nr = node[u].r;

    if (nl >= l && nr <= r)
      return node[u];

    int mid = (nl + nr) >> 1;

    if (r <= mid) return query_max_subarray_sum(u << 1, l, r);
    if (l > mid) return query_max_subarray_sum(u << 1 | 1, l, r);

    Node x = query_max_subarray_sum(u << 1, l, mid);
    Node y = query_max_subarray_sum(u << 1 | 1, mid + 1, r);
    Node ret;

    ret.sum = x.sum + y.sum;
    ret.lmax = max(x.lmax, x.sum + y.lmax);
    ret.rmax = max(y.rmax, y.sum + x.rmax);
    ret.mmax = max({x.mmax, y.mmax, x.rmax + y.lmax});

    return ret;
  }
} SGT;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  SGT.build(1, 1, n);

  int m;
  cin >> m;
  while (m--) {
    int l, r;
    cin >> l >> r;
    SegTree::Node ans = SGT.query_max_subarray_sum(1, l, r);
    cout << max({ans.lmax, ans.mmax, ans.rmax}) << endl;
  }

  return fflush(stdout), 0;
}
