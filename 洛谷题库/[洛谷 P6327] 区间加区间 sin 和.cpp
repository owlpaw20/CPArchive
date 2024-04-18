#include <cmath>
#include <iostream>

#define endl '\n'

using namespace std;
using f64 = double;

const int N = 2e5 + 5;

struct SegTree {
  struct {
    int l, r;
    f64 rsin, rcos, add;
  } node[N << 2];

  int a[N];

  void maintain(int u) {
    node[u].rsin = node[u << 1].rsin + node[u << 1 | 1].rsin;
    node[u].rcos = node[u << 1].rcos + node[u << 1 | 1].rcos;
  }

  void update_sin_cos(int u, f64 v) {
    f64 sinx = node[u].rsin, cosx = node[u].rcos;
    f64 sinv = sin(v), cosv = cos(v);

    node[u].rsin = sinx * cosv + cosx * sinv;
    node[u].rcos = cosx * cosv - sinx * sinv;
  }

  void propagate(int u) {
    if (node[u].add) {
      update_sin_cos(u << 1, node[u].add);
      update_sin_cos(u << 1 | 1, node[u].add);
      node[u << 1].add += node[u].add;
      node[u << 1 | 1].add += node[u].add;
      node[u].add = 0;
    }
  }

  void build(int u, int l, int r) {
    node[u].l = l;
    node[u].r = r;
    node[u].add = 0;

    if (l == r) {
      node[u].rsin = sin(a[l]);
      node[u].rcos = cos(a[l]);
      return;
    }

    int mid = (l + r) >> 1;

    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);

    maintain(u);
  }

  void accumulate(int u, int l, int r, f64 v) {
    int nl = node[u].l, nr = node[u].r;

    if (nl >= l && nr <= r) {
      update_sin_cos(u, v);
      node[u].add += v;
      return;
    }

    propagate(u);

    int mid = (nl + nr) >> 1;

    if (l <= mid) accumulate(u << 1, l, r, v);
    if (r > mid) accumulate(u << 1 | 1, l, r, v);

    maintain(u);
  }

  f64 query_range_sin_sum(int u, int l, int r) {
    int nl = node[u].l, nr = node[u].r;

    if (nl >= l && nr <= r)
      return node[u].rsin;

    propagate(u);

    int mid = (nl + nr) >> 1;
    f64 ret = 0;

    if (l <= mid) ret += query_range_sin_sum(u << 1, l, r);
    if (r > mid) ret += query_range_sin_sum(u << 1 | 1, l, r);

    return ret;
  }
} SGT;

int n;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed;
  cout.precision(1);

  cin >> n;
  for (int i = 1; i <= n; i++) cin >> SGT.a[i];

  SGT.build(1, 1, n);

  int m;
  cin >> m;

  while (m--) {
    int type, l, r, v;
    cin >> type >> l >> r;
    if (type == 1) {
      cin >> v;
      SGT.accumulate(1, l, r, v);
    } else
      cout << SGT.query_range_sin_sum(1, l, r) << endl;
  }

  return fflush(stdout), 0;
}
