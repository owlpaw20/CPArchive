#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;

const int N = 1e5 + 5;

struct BinIdxTree {
  i64 node[N];
  int n;

  void inc(int x, i64 v) {
    for (int i = x; i <= n; i += (i & -i))
      node[i] += v;
  }

  i64 query(int x) {
    i64 ret = 0;
    for (int i = x; i; i -= (i & -i))
      ret += node[i];
    return ret;
  }
};

int n, q;
BinIdxTree BIT1, BIT2;

i64 get_prefix_sum(int x) {
  return BIT1.query(x) * (x + 1) - BIT2.query(x);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> q;
  BIT1.n = BIT2.n = n;

  for (int i = 1, p = 0, t; i <= n; i++) {
    cin >> t;
    i64 d = t - p;
    BIT1.inc(i, d);
    BIT2.inc(i, d * i);
    p = t;
  }

  while (q--) {
    char type;
    int l, r, x;

    cin >> type >> l >> r;

    if (type == 'C') {
      cin >> x;
      BIT1.inc(l, x), BIT1.inc(r + 1, -x);
      BIT2.inc(l, 1LL * l * x), BIT2.inc(r + 1, (r + 1LL) * -x);
    } else
      cout << get_prefix_sum(r) - get_prefix_sum(l - 1) << endl;
  }

  return fflush(stdout), 0;
}
