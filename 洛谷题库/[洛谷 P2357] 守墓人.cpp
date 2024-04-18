#include <iostream>
using namespace std;
using i64 = long long;

const int N = 2e5 + 10;

int n, m;
i64 a[N];

struct Fenwick {
  i64 tr[N];
  int lowbit(int x) {
    return x & -x;
  }
  void update(int x, i64 delta) {
    for (int i = x; i <= n; i += lowbit(i))
      tr[i] += delta;
  }
  i64 query(int x) {
    i64 ret = 0;
    for (int i = x; i; i -= lowbit(i))
      ret += tr[i];
    return ret;
  }
};

Fenwick tr1, tr2;

i64 prefix(int x) {
  return tr1.query(x) * (x + 1) - tr2.query(x);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    i64 d = a[i] - a[i - 1];
    tr1.update(i, d);
    tr2.update(i, d * i);
  }

  int opt, l, r;
  i64 d;
  while (m--) {
    cin >> opt;
    if (opt == 1) {
      cin >> l >> r >> d;
      tr1.update(l, d), tr1.update(r + 1, -d);
      tr2.update(l, l * d), tr2.update(r + 1, (r + 1) * -d);
    } else if (opt == 2) {
      cin >> d;
      tr1.update(1, d), tr1.update(2, -d);
      tr2.update(1, d), tr2.update(2, 2 * -d);
    } else if (opt == 3) {
      cin >> d;
      tr1.update(1, -d), tr1.update(2, d);
      tr2.update(1, -d), tr2.update(2, 2 * d);
    } else if (opt == 4) {
      cin >> l >> r;
      cout << prefix(r) - prefix(l - 1) << endl;
    } else
      cout << prefix(1) - prefix(0) << endl;
  }
  return 0;
}
