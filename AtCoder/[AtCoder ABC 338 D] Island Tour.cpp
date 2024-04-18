#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;

const int N = 2e5 + 5;

int n, m;
int path[N];

struct SegTree {
  struct {
    int l, r;
    i64 sum, cnt;
    i64 tag_sum, tag_cnt;
  } node[N << 2];

  void propagate(int u) {
    auto &root = node[u];
    auto &left = node[u << 1];
    auto &right = node[u << 1 | 1];

    if (root.tag_sum) {
      left.tag_sum += root.tag_sum;
      right.tag_sum += root.tag_sum;
      left.sum += (left.r - left.l + 1LL) * root.tag_sum;
      right.sum += (right.r - right.l + 1LL) * root.tag_sum;
      root.tag_sum = 0;
    }

    if (root.tag_cnt) {
      left.tag_cnt += root.tag_cnt;
      right.tag_cnt += root.tag_cnt;
      left.cnt += (left.r - left.l + 1LL) * root.tag_cnt;
      right.cnt += (right.r - right.l + 1LL) * root.tag_cnt;
      root.tag_cnt = 0;
    }
  }

  void build(int u, int l, int r) {
    node[u].l = l;
    node[u].r = r;
    node[u].tag_cnt = 0;
    node[u].tag_sum = 0;

    if (l == r)
      return (void)(node[u].sum = node[u].cnt = 0);

    int mid = (l + r) >> 1;

    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
  }

  void range_upd(int u, int l, int r, int x) {
    if (l > r) return;

    int nl = node[u].l, nr = node[u].r;

    if (nl >= l && nr <= r) {
      node[u].tag_cnt += 1;
      node[u].tag_sum += x;
      node[u].cnt += nr - nl + 1LL;
      node[u].sum += (nr - nl + 1LL) * x;
      return;
    }

    propagate(u);

    int mid = (nl + nr) >> 1;

    if (l <= mid) range_upd(u << 1, l, r, x);
    if (r > mid) range_upd(u << 1 | 1, l, r, x);
  }

  auto query(int u, int x) {
    int nl = node[u].l, nr = node[u].r;

    if (nl == nr)
      return node[u];

    propagate(u);

    int mid = (nl + nr) >> 1;

    if (x <= mid) return query(u << 1, x);
    return query(u << 1 | 1, x);
  }
} SGT;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;
  SGT.build(1, 1, n);

  for (int i = 1; i <= m; i++) cin >> path[i];

  i64 len = 0;

  for (int i = 1; i < m; i++) {
    int st = min(path[i], path[i + 1]);
    int ed = max(path[i], path[i + 1]);

    if (ed - st <= n - (ed - st)) {
      len += ed - st;
      SGT.range_upd(1, st, ed - 1, ed - st);
    } else {
      len += n - (ed - st);
      SGT.range_upd(1, 1, st - 1, n - (ed - st));
      SGT.range_upd(1, ed, n, n - (ed - st));
    }
  }

  i64 ans = (1ULL << 63) - 1;

  for (int i = 1; i <= n; i++) {
    auto [l, r, sum, cnt, tgs, tgc] = SGT.query(1, i);
    ans = min(ans, len - sum + (i64)n * cnt - sum);
  }

  cout << ans << endl;
  return fflush(stdout), 0;
}
