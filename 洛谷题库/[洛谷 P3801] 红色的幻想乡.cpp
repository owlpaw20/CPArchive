#include <bits/stdc++.h>

const int MAX_N = 1e5 + 5;

int N, M;

struct SegT {
  int tr[MAX_N << 2];

  void upd(int x, int u, int nl, int nr) {
    if (nl == nr) return tr[u] ^= 1, void();
    int mid = (nl + nr) >> 1;
    if (x <= mid) upd(x, u << 1, nl, mid);
    else upd(x, u << 1 | 1, mid + 1, nr);
    tr[u] = tr[u << 1] + tr[u << 1 | 1];
  }

  int qry(int l, int r, int u, int nl, int nr) {
    if (nl >= l && nr <= r) return tr[u];
    int mid = (nl + nr) >> 1;
    if (r <= mid) return qry(l, r, u << 1, nl, mid);
    if (l > mid) return qry(l, r, u << 1 | 1, mid + 1, nr);
    return qry(l, r, u << 1, nl, mid) + qry(l, r, u << 1 | 1, mid + 1, nr);
  }
} Tx, Ty;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int q;
  std::cin >> N >> M >> q;

  while (q--) {
    static int type;
    std::cin >> type;

    if (type == 1) {
      static int x, y;
      std::cin >> x >> y;
      Tx.upd(x, 1, 1, N), Ty.upd(y, 1, 1, M);
    }

    else {
      static int x, y, xx, yy;
      std::cin >> x >> y >> xx >> yy;
      int cntX = Tx.qry(x, xx, 1, 1, N), cntY = Ty.qry(y, yy, 1, 1, M);
      std::cout << (yy - y + 1LL) * cntX + (xx - x + 1LL) * cntY - 2LL * cntX * cntY << '\n';
    }

    std::cerr << Tx.tr[1] << ' ' << Ty.tr[1] << '\n';
  }

  std::cout.flush();
  return 0;
}
