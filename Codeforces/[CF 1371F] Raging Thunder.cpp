#include <bits/stdc++.h>

const int MAX_N = 5e5 + 5;

int N;
bool a[MAX_N];

struct SegT {
  struct Node {
    int len;
    int lmax, rmax;
    int lsmax, rsmax;
    int max01, max10;
    bool ltype, rtype;
    bool tag;

    void pull(const Node& L, const Node& R) {
      len = L.len + R.len;
      ltype = L.ltype, rtype = R.rtype;

      lmax = (L.lmax == L.len && R.ltype == L.ltype) ? (L.len + R.lmax) : L.lmax;
      rmax = (R.rmax == R.len && L.rtype == R.rtype) ? (R.len + L.rmax) : R.rmax;

      if (L.lmax == L.len) lsmax = L.len + ((L.ltype == R.ltype) ? R.lsmax : R.lmax);
      else if (L.lsmax == L.len && L.rtype == R.ltype) lsmax = L.len + R.lmax;
      else lsmax = L.lsmax;
      if (R.rmax == R.len) rsmax = R.len + ((R.rtype == L.rtype) ? L.rsmax : L.rmax);
      else if (R.rsmax == R.len && R.ltype == L.rtype) rsmax = R.len + L.rmax;
      else rsmax = R.rsmax;

      max01 = std::max(L.max01, R.max01);
      max10 = std::max(L.max10, R.max10);
      if (L.rtype == 0 && R.ltype == 1) max01 = std::max(max01, L.rmax + R.lmax);
      else if (L.rtype == 0 && R.ltype == 0) max01 = std::max(max01, L.rmax + R.lsmax);
      else if (L.rtype == 1 && R.ltype == 1) max01 = std::max(max01, L.rsmax + R.lmax);
      if (L.rtype == 1 && R.ltype == 0) max10 = std::max(max10, L.rmax + R.lmax);
      else if (L.rtype == 1 && R.ltype == 1) max10 = std::max(max10, L.rmax + R.lsmax);
      else if (L.rtype == 0 && R.ltype == 0) max10 = std::max(max10, L.rsmax + R.lmax);
    }

    void flip() {
      tag = !tag;
      ltype = !ltype, rtype = !rtype;
      std::swap(max10, max01);
    }

    void push(Node& L, Node& R) {
      if (!tag) return;
      L.flip(), R.flip();
      tag = 0;
    }
  } tr[MAX_N << 2];

  void init(int u = 1, int nl = 1, int nr = N) {
    if (nl == nr) {
      tr[u].len = 1;
      tr[u].ltype = tr[u].rtype = a[nl];
      tr[u].lmax = tr[u].rmax = tr[u].lsmax = tr[u].rsmax = tr[u].max10 = tr[u].max01 = 1;
      return;
    }
    int mid = (nl + nr) >> 1;
    init(u << 1, nl, mid), init(u << 1 | 1, mid + 1, nr);
    tr[u].pull(tr[u << 1], tr[u << 1 | 1]);
  }

  void flip(int l, int r, int u = 1, int nl = 1, int nr = N) {
    if (nl >= l && nr <= r) return tr[u].flip();
    tr[u].push(tr[u << 1], tr[u << 1 | 1]);
    int mid = (nl + nr) >> 1;
    if (l <= mid) flip(l, r, u << 1, nl, mid);
    if (r > mid) flip(l, r, u << 1 | 1, mid + 1, nr);
    tr[u].pull(tr[u << 1], tr[u << 1 | 1]);
  }

  Node query(int l, int r, int u = 1, int nl = 1, int nr = N) {
    if (nl >= l && nr <= r) return tr[u];
    tr[u].push(tr[u << 1], tr[u << 1 | 1]);
    int mid = (nl + nr) >> 1;
    if (r <= mid) return query(l, r, u << 1, nl, mid);
    if (l > mid) return query(l, r, u << 1 | 1, mid + 1, nr);
    Node ret, lc = query(l, r, u << 1, nl, mid), rc = query(l, r, u << 1 | 1, mid + 1, nr);
    ret.pull(lc, rc);
    return ret;
  }
} T;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int M;
  std::cin >> N >> M;

  for (int i = 1; i <= N; ++i) {
    static char c;
    std::cin >> c;
    a[i] = c == '<';
  }

  T.init();

  while (M--) {
    static int l, r;
    std::cin >> l >> r, T.flip(l, r);
    std::cout << T.query(l, r).max01 << '\n';
  }

  std::cout.flush();
  return 0;
}
