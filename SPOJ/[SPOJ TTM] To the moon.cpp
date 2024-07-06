#include <cstring>
#include <iostream>

const int MAX_N = 1e5 + 5;

using LL = long long;

int N;
int root[MAX_N], now;

struct PSegT {
  struct Node {
    int l, r;
    LL sum, tag;
  } tr[MAX_N << 5];

  int size;

  void pull(int u) { tr[u].sum = tr[tr[u].l].sum + tr[tr[u].r].sum; }

  int init(int nl = 1, int nr = N) {
    int u = ++size;
    if (nl == nr) return std::cin >> tr[u].sum, u;
    int mid = (nl + nr) >> 1;
    tr[u].l = init(nl, mid);
    tr[u].r = init(mid + 1, nr);
    return pull(u), u;
  }

  int upd(int l, int r, LL x, int u = 1, int nl = 1, int nr = N) {
    int v = ++size;
    tr[v] = tr[u];
    tr[v].sum += (r - l + 1LL) * x;

    if (l == nl && r == nr) return tr[v].tag += x, v;

    int mid = (nl + nr) >> 1;

    if (r <= mid) return tr[v].l = upd(l, r, x, tr[u].l, nl, mid), v;
    if (l > mid) return tr[v].r = upd(l, r, x, tr[u].r, mid + 1, nr), v;
    tr[v].l = upd(l, mid, x, tr[u].l, nl, mid);
    tr[v].r = upd(mid + 1, r, x, tr[u].r, mid + 1, nr);
    return v;
  }

  LL qry(int l, int r, int u = 1, int nl = 1, int nr = N, LL tags = 0) {
    if (l == nl && r == nr) return tr[u].sum + (r - l + 1LL) * tags;
    int mid = (nl + nr) >> 1;
    if (r <= mid) return qry(l, r, tr[u].l, nl, mid, tags + tr[u].tag);
    if (l > mid) return qry(l, r, tr[u].r, mid + 1, nr, tags + tr[u].tag);
    return qry(l, mid, tr[u].l, nl, mid, tags + tr[u].tag) + qry(mid + 1, r, tr[u].r, mid + 1, nr, tags + tr[u].tag);
  }

#undef L
#undef R
} T;

void solve() {
  memset(&T.tr, 0, sizeof(PSegT::Node) * (N << 5));
  memset(root, 0, sizeof(int) * (N + 1));

  static int q;
  std::cin >> q;

  T.size = 0;
  root[now = 0] = T.init();

  while (q--) {
    static char type;
    static int a, b, c;

    std::cin >> type;

    if (type == 'C') {
      std::cin >> a >> b >> c, ++now;
      root[now] = T.upd(a, b, c, root[now - 1]);
    } else if (type == 'Q') {
      std::cin >> a >> b;
      std::cout << T.qry(a, b, root[now]) << '\n';
    } else if (type == 'H') {
      std::cin >> a >> b >> c;
      std::cout << T.qry(a, b, root[c]) << '\n';
    } else
      std::cin >> now;
  }

  std::cout << std::endl;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  while (std::cin >> N) solve();

  return 0;
}
