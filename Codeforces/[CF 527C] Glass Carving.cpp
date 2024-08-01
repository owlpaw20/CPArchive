#include <bits/stdc++.h>

using LL = long long;

const int MAX_N = 2e5 + 5;

struct SegT {
  struct Node {
    int len;
    int max, lmax, rmax;
  } tr[MAX_N << 2];

  void pull(int u, int lc, int rc) {
    tr[u].lmax = (tr[lc].len == tr[lc].lmax) ? tr[lc].len + tr[rc].lmax : tr[lc].lmax;
    tr[u].rmax = (tr[rc].len == tr[rc].rmax) ? tr[rc].len + tr[lc].rmax : tr[rc].rmax;
    tr[u].max = std::max({tr[lc].max, tr[lc].rmax + tr[rc].lmax, tr[rc].max});
  }

  void init(int u, int nl, int nr) {
    tr[u].len = nr - nl + 1;
    if (nl == nr) return tr[u].max = tr[u].lmax = tr[u].rmax = 1, void();
    int mid = (nl + nr) >> 1;
    init(u << 1, nl, mid);
    init(u << 1 | 1, mid + 1, nr);
    pull(u, u << 1, u << 1 | 1);
  }

  void upd(int x, int u, int nl, int nr) {
    if (nl == nr) return tr[u].max = tr[u].lmax = tr[u].rmax = 0, void();
    int mid = (nl + nr) >> 1;
    if (x <= mid) upd(x, u << 1, nl, mid);
    else upd(x, u << 1 | 1, mid + 1, nr);
    pull(u, u << 1, u << 1 | 1);
  }
} vT, hT;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int W, H, q;
  std::cin >> W >> H >> q;

  hT.init(1, 1, W - 1);  // 水平
  vT.init(1, 1, H - 1);  // 垂直

  while (q--) {
    static char type;
    static int x;
    std::cin >> type >> x;

    switch (type) {
      case 'H': vT.upd(x, 1, 1, H - 1); break;
      case 'V': hT.upd(x, 1, 1, W - 1); break;
    }

    std::cout << (LL)(vT.tr[1].max + 1) * (hT.tr[1].max + 1) << '\n';
  }

  std::cout.flush();
  return 0;
}
