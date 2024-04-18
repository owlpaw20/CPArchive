#include <iostream>
using namespace std;

const int N = 2e5 + 10;

int n, m, a[N];

struct SegTree {
  struct Node {
    int l, r;
    int sum, tag;
  } tree[4 * N];
  void propagate(int u) {
    Node &root = tree[u];
    Node &left = tree[2 * u];
    Node &right = tree[2 * u + 1];
    if (root.tag) {
      left.tag ^= 1;
      right.tag ^= 1;
      left.sum = (left.r - left.l + 1) - left.sum;
      right.sum = (right.r - right.l + 1) - right.sum;
      root.tag = 0;
    }
  }
  void build(int u, int l, int r) {
    if (l == r)
      tree[u] = {l, r, a[l], 0};
    else {
      tree[u] = {l, r};
      int mid = (l + r) >> 1;
      if (l <= mid) build(2 * u, l, mid);
      if (r > mid) build(2 * u + 1, mid + 1, r);
      tree[u].sum = tree[2 * u].sum + tree[2 * u + 1].sum;
    }
  }
  int query(int u, int l, int r) {
    int tl = tree[u].l, tr = tree[u].r;
    if (tl >= l && tr <= r) return tree[u].sum;
    propagate(u);
    int ret = 0, mid = (tl + tr) >> 1;
    if (l <= mid) ret += query(2 * u, l, r);
    if (r > mid) ret += query(2 * u + 1, l, r);
    return ret;
  }
  void update(int u, int l, int r) {
    int tl = tree[u].l, tr = tree[u].r;
    if (tl >= l && tr <= r) {
      tree[u].sum = (tr - tl + 1) - tree[u].sum;
      tree[u].tag ^= 1;
      return;
    }
    propagate(u);
    int mid = (tl + tr) >> 1;
    if (l <= mid) update(2 * u, l, r);
    if (r > mid) update(2 * u + 1, l, r);
    tree[u].sum = tree[2 * u].sum + tree[2 * u + 1].sum;
  }
} tr;

int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    char t;
    cin >> t;
    a[i] = t - '0';
  }
  tr.build(1, 1, n);
  while (m--) {
    int opt, a, b;
    cin >> opt >> a >> b;
    if (opt == 0)
      tr.update(1, a, b);
    else if (opt == 1)
      cout << tr.query(1, a, b) << endl;
  }
  return 0;
}
