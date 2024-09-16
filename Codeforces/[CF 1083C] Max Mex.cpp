#include <bits/stdc++.h>

const int MAX_N = 2e5 + 5;

int N, p[MAX_N], loc[MAX_N];

int ed[MAX_N], nx[MAX_N], head[MAX_N], idx;
void connect(int u, int v) { ed[idx] = v, nx[idx] = head[u], head[u] = idx++; }

int dfn[MAX_N], ver[MAX_N << 2], ts;
int dep[MAX_N];

// 预处理欧拉序和节点深度
void DFS(int u, int fa) {
  dfn[u] = ++ts;
  ver[ts] = u;
  dep[u] = dep[fa] + 1;
  for (int i = head[u]; ~i; i = nx[i]) DFS(ed[i], u), ver[++ts] = u;
}

// O(n log n) — O(1) 求 LCA
struct SparseTable {
  int f[20][MAX_N << 1];
  int g[20][MAX_N << 1];

  void init() {
    for (int i = 1; i <= ts; ++i) f[0][i] = ver[i], g[0][i] = dep[ver[i]];
    int lim = std::min(19, std::__lg(N) + 1);
    for (int i = 1; i <= lim; ++i)
      for (int j = 1; j + (1 << i) - 1 <= ts; ++j) {
        bool tmp = g[i - 1][j] < g[i - 1][j + (1 << (i - 1))];
        f[i][j] = tmp ? f[i - 1][j] : f[i - 1][j + (1 << (i - 1))];
        g[i][j] = tmp ? g[i - 1][j] : g[i - 1][j + (1 << (i - 1))];
      }
  }

  int qry(int l, int r) {
    if (l > r) std::swap(l, r);
    int t = std::__lg(r - l + 1);
    return g[t][l] < g[t][r - (1 << t) + 1] ? f[t][l] : f[t][r - (1 << t) + 1];
  }
} ST;

// 判断 z 是否在 x 到 y 的路径上
bool check(int x, int y, int z) {
  auto dist = [&](int a, int b) { return dep[a] + dep[b] - 2 * dep[ST.qry(dfn[a], dfn[b])]; };
  return dist(x, y) == dist(x, z) + dist(z, y);
}

struct SegT {
  struct Node {
    int x, y;         // 区间内的颜色所在的节点所组成的链的两个端点
    bool is_on_path;  // 区间内的颜色所在的节点是否能组成一条链
  } tr[MAX_N << 2];   // 维护每一个颜色所在的节点编号

  using cNodeRef = const Node &;

  Node merge(cNodeRef L, cNodeRef R) {
    if (!L.is_on_path || !R.is_on_path) return (Node){-1, -1, false};

    // 枚举并判断四个端点中选择两个作为父节点所代表链的两个端点是否合法
    if (check(L.x, L.y, R.x) && check(L.x, L.y, R.y)) return (Node){L.x, L.y, true};
    if (check(L.x, R.x, L.y) && check(L.x, R.x, R.y)) return (Node){L.x, R.x, true};
    if (check(L.x, R.y, L.y) && check(L.x, R.y, R.x)) return (Node){L.x, R.y, true};
    if (check(L.y, R.x, L.x) && check(L.y, R.x, R.y)) return (Node){L.y, R.x, true};
    if (check(L.y, R.y, L.x) && check(L.y, R.y, R.x)) return (Node){L.y, R.y, true};
    if (check(R.x, R.y, L.x) && check(R.x, R.y, L.y)) return (Node){R.x, R.y, true};

    return (Node){-1, -1, false};
  }

  void build(int u = 1, int nl = 0, int nr = N) {
    if (nl == nr) return tr[u] = (Node){loc[nl], loc[nl], true}, void();
    int mid = (nl + nr) >> 1;
    build(u << 1, nl, mid);
    build(u << 1 | 1, mid + 1, nr);
    tr[u] = merge(tr[u << 1], tr[u << 1 | 1]);
  }

  void upd(int x, int val, int u = 1, int nl = 0, int nr = N) {
    if (nl == nr) return tr[u].x = tr[u].y = val, void();
    int mid = (nl + nr) >> 1;
    if (x <= mid) upd(x, val, u << 1, nl, mid);
    else upd(x, val, u << 1 | 1, mid + 1, nr);
    tr[u] = merge(tr[u << 1], tr[u << 1 | 1]);
  }

  // 线段树二分判断链的断点
  // 注意线段树最右端点是 N 而不是 N - 1（如果在已有颜色中找不到，则 mex 就是 N）
  int qry(cNodeRef tmp, int u = 1, int nl = 0, int nr = N) {
    if (nl == nr) return nr;  // 如果找到链的断点，则返回

    // 尝试合并已成的链与左区间的链
    Node t = !tmp.x && !tmp.y ? tr[u << 1] : merge(tr[u << 1], tmp);

    int mid = (nl + nr) >> 1;
    if (t.is_on_path) return qry(t, u << 1 | 1, mid + 1, nr);  // 如果可以合并则断点在右区间
    return qry(tmp, u << 1, nl, mid);                          // 否则断点在左区间
  }
} T;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  memset(head, -1, sizeof(int) * (N + 1));
  for (int i = 1; i <= N; ++i) std::cin >> p[i], loc[p[i]] = i;
  for (int i = 2, d; i <= N; ++i) std::cin >> d, connect(d, i);

  DFS(1, 0);
  ST.init();
  T.build();

  int q;
  std::cin >> q;

  while (q--) {
    static int type, x, y;
    std::cin >> type;

    if (type == 1) {
      std::cin >> x >> y;
      T.upd(p[x], y), T.upd(p[y], x);  // 将 x 节点的颜色所在的位置修改为 y，反之亦然
      std::swap(p[x], p[y]);           // 更新两个节点的颜色
    } else
      std::cout << T.qry({0, 0, true}) << '\n';
  }

  std::cout.flush();
  return 0;
}
