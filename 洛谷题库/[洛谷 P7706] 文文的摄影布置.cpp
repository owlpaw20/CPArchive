// 参考题解：https://www.luogu.com.cn/article/oj2vo7sx

#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;

const int N = 5e5 + 5;
const int INF = (1LL << 31) - 1;

int n, m;
int a[N], b[N];

#define nl (node[u].l)
#define nr (node[u].r)

struct SegTree {
  struct Node {
    int l, r;
    int x, y, p, q, ans;
  } node[N << 2];

  Node pushup(Node lc, Node rc) {
    Node rt;
    rt.l = lc.l, rt.r = rc.r;
    rt.x = max(lc.x, rc.x);
    rt.y = min(lc.y, rc.y);
    rt.p = max({lc.p, rc.p, lc.x - rc.y});
    rt.q = max({lc.q, rc.q, rc.x - lc.y});
    rt.ans = max({lc.ans, rc.ans, lc.p + rc.x, lc.x + rc.q});
    return rt;
  }

  void build(int l = 1, int r = n, int u = 1) {
    nl = l, nr = r;

    if (l == r) {
      node[u].x = a[l];
      node[u].y = b[l];
      node[u].p = -INF;
      node[u].q = -INF;
      node[u].ans = -INF;
      return;
    }

    int mid = (l + r) >> 1;

    build(l, mid, u << 1);
    build(mid + 1, r, u << 1 | 1);

    node[u] = pushup(node[u << 1], node[u << 1 | 1]);
  }

  void update(int x, int y, int v, int u = 1) {
    if (nl == nr) {
      if (v == 1)
        node[u].x = y;
      else
        node[u].y = y;
      return;
    }

    int mid = (nl + nr) >> 1;

    if (x <= mid)
      update(x, y, v, u << 1);
    else
      update(x, y, v, u << 1 | 1);

    node[u] = pushup(node[u << 1], node[u << 1 | 1]);
  }

  Node query(int l, int r, int u = 1) {
    if (nl >= l && nr <= r)
      return node[u];

    int mid = (nl + nr) >> 1;

    if (r <= mid) return query(l, r, u << 1);
    if (l > mid) return query(l, r, u << 1 | 1);

    return pushup(query(l, r, u << 1), query(l, r, u << 1 | 1));
  }
} SGT;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= n; i++) cin >> b[i];

  SGT.build();

  while (m--) {
    int type, x, y;
    cin >> type >> x >> y;

    if (type < 3)
      SGT.update(x, y, type);
    else
      cout << SGT.query(x, y).ans << endl;
  }
  return fflush(stdout), 0;
}
