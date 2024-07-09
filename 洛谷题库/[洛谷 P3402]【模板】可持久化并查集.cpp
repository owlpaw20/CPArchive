#include <iostream>

const int MAX_N = 1e5 + 5;
const int MAX_M = 2e5 + 5;
const int MAX_SIZE = MAX_N * 2 + MAX_M * 40;

int N;

struct PerUnionFind {
  struct Node {
    int l, r;
    int fa, depth;
  } tr[MAX_SIZE];

  int size;
  int root[MAX_M];

  int init(int nl = 1, int nr = N) {
    int u = ++size;
    if (nl == nr) return tr[u].fa = nl, tr[u].depth = 0, u;
    int mid = (nl + nr) >> 1;
    tr[u].l = init(nl, mid);
    tr[u].r = init(mid + 1, nr);
    return u;
  }

  int upd_fa(int x, int fa, int u, int nl = 1, int nr = N) {
    int v = ++size;
    tr[v] = tr[u];
    if (nl == nr) return tr[v].fa = fa, v;
    int mid = (nl + nr) >> 1;
    if (x <= mid) tr[v].l = upd_fa(x, fa, tr[u].l, nl, mid);
    else tr[v].r = upd_fa(x, fa, tr[u].r, mid + 1, nr);
    return v;
  }

  int upd_depth(int x, int u, int nl = 1, int nr = N) {
    int v = ++size;
    tr[v] = tr[u];
    if (nl == nr) return ++tr[v].depth, v;
    int mid = (nl + nr) >> 1;
    if (x <= mid) tr[v].l = upd_depth(x, tr[u].l, nl, mid);
    else tr[v].r = upd_depth(x, tr[u].r, mid + 1, nr);
    return v;
  }

  int qry(int x, int u, int nl = 1, int nr = N) {
    if (nl == nr) return u;
    int mid = (nl + nr) >> 1;
    if (x <= mid) return qry(x, tr[u].l, nl, mid);
    else return qry(x, tr[u].r, mid + 1, nr);
  }

  int find(int t, int x) {
    int fa = qry(x, root[t]);
    if (tr[fa].fa == x) return fa;
    return find(t, tr[fa].fa);
  }

  void merge(int t, int x, int y) {
    root[t] = root[t - 1];
    x = find(t, x), y = find(t, y);
    if (tr[x].fa != tr[y].fa) {
      if (tr[x].depth > tr[y].depth) std::swap(x, y); // 按秩合并
      root[t] = upd_fa(tr[x].fa, tr[y].fa, root[t - 1]); // 小深度往大深度合并
      if (tr[x].depth == tr[y].depth) root[t] = upd_depth(tr[y].fa, root[t]);
    }
  }

  bool check(int t, int x, int y) {
    x = find(t, x), y = find(t, y);
    return tr[x].fa == tr[y].fa;
  }
} pDSU;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int M;
  std::cin >> N >> M;

  pDSU.root[0] = pDSU.init();

  for (int i = 1; i <= M; ++i) {
    static int type, a, b;
    std::cin >> type >> a;
    if (type & 1) std::cin >> b;

    if (type == 1) pDSU.merge(i, a, b);
    else if (type == 2) pDSU.root[i] = pDSU.root[a];
    else std::cout << pDSU.check(i - 1, a, b) << '\n', pDSU.root[i] = pDSU.root[i - 1];
  }

  std::cout.flush();
  return 0;
}
