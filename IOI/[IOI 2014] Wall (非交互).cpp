#include <vector>
#include <climits>
#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;

struct SegTree {
  struct Node {
    int l, r;
    int Max, Min;
  };

  vector<Node> tree;

  void init(int n) {
    tree.clear();
    tree.resize(n * 4 + 20);
  }

  void propagate(int u) {
    Node &root = tree[u];
    Node &left = tree[u << 1];
    Node &right = tree[u << 1 | 1];

    if (root.Max != 0) {
      left.Min = max(left.Min, root.Max);
      left.Max = max(left.Max, root.Max);
      right.Min = max(right.Min, root.Max);
      right.Max = max(right.Max, root.Max);
      root.Max = 0;
    }
    if (root.Min != INT_MAX) {
      left.Min = min(left.Min, root.Min);
      left.Max = min(left.Max, root.Min);
      right.Min = min(right.Min, root.Min);
      right.Max = min(right.Max, root.Min);
      root.Min = INT_MAX;
    }
  }

  void build(int l, int r, int u = 1) {
    tree[u] = {l, r, 0, INT_MAX};
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(l, mid, u << 1);
    build(mid + 1, r, u << 1 | 1);
  }

  void update_max(int l, int r, int x, int u = 1) {
    int tl = tree[u].l, tr = tree[u].r;
    if (tl >= l && tr <= r) {
      tree[u].Min = max(x, tree[u].Min);
      tree[u].Max = max(x, tree[u].Max);
      return;
    }
    propagate(u);
    int mid = (tl + tr) >> 1;
    if (l <= mid) update_max(l, r, x, u << 1);
    if (r > mid) update_max(l, r, x, u << 1 | 1);
  }

  void update_min(int l, int r, int x, int u = 1) {
    int tl = tree[u].l, tr = tree[u].r;
    if (tl >= l && tr <= r) {
      tree[u].Min = min(x, tree[u].Min);
      tree[u].Max = min(x, tree[u].Max);
      return;
    }
    propagate(u);
    int mid = (tl + tr) >> 1;
    if (l <= mid) update_min(l, r, x, u << 1);
    if (r > mid) update_min(l, r, x, u << 1 | 1);
  }

  void query(int l, int r, int u = 1) {
    int tl = tree[u].l, tr = tree[u].r;
    if (tl == tr)
      return (void)(cout << tree[u].Max << endl);
    propagate(u);
    int mid = (tl + tr) >> 1;
    query(l, mid, u << 1);
    query(mid + 1, r, u << 1 | 1);
  }
};

int n, K;
SegTree SGT;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> K;
  SGT.init(n);
  SGT.build(1, n);

  while (K--) {
    int type, l, r, x;
    cin >> type >> l >> r >> x;
    l += 1, r += 1;
    if (type == 1)
      SGT.update_max(l, r, x);
    else
      SGT.update_min(l, r, x);
  }

  SGT.query(1, n);

  fflush(stdout);
  return 0;
}
