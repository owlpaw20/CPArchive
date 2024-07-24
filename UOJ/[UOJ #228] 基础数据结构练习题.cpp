#include <cmath>
#include <iostream>

using LL = long long;

constexpr int MAX_N = 1e5 + 5;

int N, M;
int a[MAX_N];

template <typename intT>
intT _sqrt(intT x) { return floor(sqrt(x)); }

struct SegT {
  struct Node {
    int len;
    LL sum, min, max, tag;

    Node operator+(const Node& t) const {
      return (Node){
        len + t.len,
        sum + t.sum,
        std::min(min, t.min),
        std::max(max, t.max),
        0,
      };
    }

    void modify(LL t) {
      sum += t * len;
      max += t, min += t, tag += t;
    }

    void push(Node& L, Node& R) {
      if (!tag) return;
      L.modify(tag);
      R.modify(tag);
      tag = 0;
    }
  } tr[MAX_N << 5];

  void init(int u = 1, int nl = 1, int nr = N) {
    if (nl == nr) return tr[u] = {1, a[nl], a[nl], a[nl], 0}, void();
    int mid = (nl + nr) >> 1;
    init(u << 1, nl, mid);
    init(u << 1 | 1, mid + 1, nr);
    tr[u] = tr[u << 1] + tr[u << 1 | 1];
  }

  void range_add(int l, int r, LL v, int u = 1, int nl = 1, int nr = N) {
    if (nl >= l && nr <= r) return tr[u].modify(v);
    tr[u].push(tr[u << 1], tr[u << 1 | 1]);
    int mid = (nl + nr) >> 1;
    if (l <= mid) range_add(l, r, v, u << 1, nl, mid);
    if (r > mid) range_add(l, r, v, u << 1 | 1, mid + 1, nr);
    tr[u] = tr[u << 1] + tr[u << 1 | 1];
  }

  void range_sqrt(int l, int r, int u = 1, int nl = 1, int nr = N) {
    if (nl >= l && nr <= r) {
      int sq_max = _sqrt(tr[u].max), sq_min = _sqrt(tr[u].min);
      if (tr[u].max == tr[u].min || (tr[u].max == tr[u].min + 1 && sq_max == sq_min + 1))
        return tr[u].modify(sq_max - tr[u].max);
    }
    tr[u].push(tr[u << 1], tr[u << 1 | 1]);
    int mid = (nl + nr) >> 1;
    if (l <= mid) range_sqrt(l, r, u << 1, nl, mid);
    if (r > mid) range_sqrt(l, r, u << 1 | 1, mid + 1, nr);
    tr[u] = tr[u << 1] + tr[u << 1 | 1];
  }

  LL qry(int l, int r, int u = 1, int nl = 1, int nr = N) {
    if (nl >= l && nr <= r) return tr[u].sum;
    tr[u].push(tr[u << 1], tr[u << 1 | 1]);
    int mid = (nl + nr) >> 1;
    if (r <= mid) return qry(l, r, u << 1, nl, mid);
    if (l > mid) return qry(l, r, u << 1 | 1, mid + 1, nr);
    return qry(l, r, u << 1, nl, mid) + qry(l, r, u << 1 | 1, mid + 1, nr);
  }
} T;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;
  for (int i = 1; i <= N; ++i) std::cin >> a[i];

  T.init();

  while (M--) {
    static int type, l, r, x;
    std::cin >> type >> l >> r;

    if (type == 1) std::cin >> x, T.range_add(l, r, x);
    if (type == 2) T.range_sqrt(l, r);
    if (type == 3) std::cout << T.qry(l, r) << '\n';
  }

  std::cout.flush();
  return 0;
}
