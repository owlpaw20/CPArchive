#include <bits/stdc++.h>

using i64 = long long;

const int MAX_N = 2e5 + 5;

int N, a[MAX_N];

struct SegT {
  struct Node {
    int lmo, rmo, len;
    i64 llen, rlen, sum;
  } tr[MAX_N << 2];

  Node merge(const Node& L, const Node& R) {
    static Node ret;
    ret.lmo = L.lmo;
    ret.rmo = R.rmo;
    ret.len = L.len + R.len;
    ret.llen = L.rmo <= R.lmo && L.llen == L.len ? L.len + R.llen : L.llen;
    ret.rlen = L.rmo <= R.lmo && R.rlen == R.len ? R.len + L.rlen : R.rlen;
    ret.sum = L.sum + R.sum + L.rlen * R.llen * (L.rmo <= R.lmo);
    return ret;
  }

  void build(int u = 1, int nl = 1, int nr = N) {
    if (nl == nr) return tr[u] = {a[nl], a[nl], 1, 1, 1, 1}, void();
    int mid = (nl + nr) >> 1;
    build(u << 1, nl, mid);
    build(u << 1 | 1, mid + 1, nr);
    tr[u] = merge(tr[u << 1], tr[u << 1 | 1]);
  }

  void upd(int x, int val, int u = 1, int nl = 1, int nr = N) {
    if (nl == nr) return tr[u].lmo = tr[u].rmo = val, void();
    int mid = (nl + nr) >> 1;
    if (x <= mid) upd(x, val, u << 1, nl, mid);
    else upd(x, val, u << 1 | 1, mid + 1, nr);
    tr[u] = merge(tr[u << 1], tr[u << 1 | 1]);
  }

  Node qry(int l, int r, int u = 1, int nl = 1, int nr = N) {
    if (nl >= l && nr <= r) return tr[u];
    int mid = (nl + nr) >> 1;
    if (r <= mid) return qry(l, r, u << 1, nl, mid);
    if (l > mid) return qry(l, r, u << 1 | 1, mid + 1, nr);
    return merge(qry(l, r, u << 1, nl, mid), qry(l, r, u << 1 | 1, mid + 1, nr));
  }
} T;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int q;
  std::cin >> N >> q;
  for (int i = 1; i <= N; ++i) std::cin >> a[i];

  T.build();

  while (q--) {
    static int type, x, y;
    std::cin >> type >> x >> y;

    if (type == 1) T.upd(x, y);
    else std::cout << T.qry(x, y).sum << '\n';
  }

  std::cout.flush();
  return 0;
}
