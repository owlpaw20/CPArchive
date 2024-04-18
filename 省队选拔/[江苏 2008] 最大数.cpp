#include <iostream>

#define endl '\n'
#define prev Prev

using namespace std;
using Long = long long;

const int N = 2e5 + 10;

struct SegmentTree {
  struct Node {
    Long l, r, val;
    Node() : l(0), r(0), val(0) {}
  } tree[4 * N];

  void build(Long v, Long l, Long r) {
    tree[v].l = l, tree[v].r = r;
    if (l == r) return;
    Long mid = (l + r) >> 1;
    build(2 * v, l, mid);
    build(2 * v + 1, mid + 1, r);
  }

  Long query(Long v, Long l, Long r) {
    Long tl = tree[v].l, tr = tree[v].r;
    if (tl >= l && tr <= r)
      return tree[v].val;
    Long mid = (tl + tr) >> 1;
    Long ret = 0;
    if (l <= mid) ret = max(ret, query(2 * v, l, r));
    if (r > mid) ret = max(ret, query(2 * v + 1, l, r));
    return ret;
  }

  void modify(Long v, Long target, Long value) {
    Long tl = tree[v].l, tr = tree[v].r;
    if (tl == tr) {
      tree[v].val = value;
      return;
    }
    Long mid = (tl + tr) >> 1;
    if (target <= mid)
      modify(2 * v, target, value);
    else
      modify(2 * v + 1, target, value);
    Long lc = tree[2 * v].val, rc = tree[2 * v + 1].val;
    tree[v].val = max(lc, rc);
  }
} tr;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  Long m, p, prev = 0, size = 0;

  cin >> m >> p;
  tr.build(1, 1, m);

  while (m--) {
    char opt;
    cin >> opt;
    if (opt == 'A') {
      Long t;
      cin >> t;
      t = (t + prev) % p;
      tr.modify(1, ++size, t);
    } else if (opt == 'Q') {
      Long t;
      cin >> t;
      prev = tr.query(1, size - t + 1, size);
      cout << prev << endl;
    }
  }

  fflush(stdout);
  return 0;
}
