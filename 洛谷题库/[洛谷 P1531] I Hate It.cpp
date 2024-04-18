#include <iostream>
using namespace std;

const int N = 2e5 + 10;

int n, m, a[N];

struct SegmentTree {
  struct Node {
    int l, r, val;
  } tree[4 * N];
  void build(int u, int l, int r) {
    tree[u].l = l, tree[u].r = r;
    if (l == r) {
      tree[u].val = a[l];
      return;
    }
    int mid = (l + r) >> 1;
    build(2 * u, l, mid);
    build(2 * u + 1, mid + 1, r);
    int ls = tree[2 * u].val, rs = tree[2 * u + 1].val;
    tree[u].val = max(ls, rs);
  }
  int query(int u, int l, int r) {
    int tl = tree[u].l, tr = tree[u].r;
    if (tl >= l && tr <= r)
      return tree[u].val;
    int mid = (tl + tr) >> 1;
    int ret = 0;
    if (l <= mid) ret = max(ret, query(2 * u, l, r));
    if (r > mid) ret = max(ret, query(2 * u + 1, l, r));
    return ret;
  }
  void update(int u, int target, int value) {
    int tl = tree[u].l, tr = tree[u].r;
    if (tl == tr) {
      tree[u].val = value;
      return;
    }
    int mid = (tl + tr) >> 1;
    if (target <= mid)
      update(2 * u, target, value);
    else
      update(2 * u + 1, target, value);
    int lc = tree[2 * u].val, rc = tree[2 * u + 1].val;
    tree[u].val = max(lc, rc);
  }
};

SegmentTree tr;

int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> a[i];
  tr.build(1, 1, n);
  while (m--) {
    char opt;
    cin >> opt;
    if (opt == 'Q') {
      int l, r;
      cin >> l >> r;
      cout << tr.query(1, l, r) << endl;
    } else {
      int a, gb;
      cin >> a >> gb;
      int ga = tr.query(1, a, a);
      if (ga < gb) tr.update(1, a, gb);
    }
  }
  return 0;
}
