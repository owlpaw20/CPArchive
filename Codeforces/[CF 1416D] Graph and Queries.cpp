#include <bits/stdc++.h>

namespace FastIO {
  const int MAX_BUF = 1 << 16;
  char buf[MAX_BUF], *p1, *p2;
  char pbuf[MAX_BUF], *pp = pbuf;

  char getchar() { return (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAX_BUF, stdin), p1 == p2) ? EOF : *p1++); }
  void putchar(char c) { (((pp - pbuf == MAX_BUF) && (fwrite(pbuf, 1, MAX_BUF, stdout), pp = pbuf)), *pp++ = c); }
  void flush() { (pp - pbuf) && fwrite(pbuf, 1, pp - pbuf, stdout); }

  template <typename T = int>
  T read() {
    short int f = 1;
    T var = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
      if (ch == '-') f = -f;
      ch = getchar();
    }
    while (ch >= '0' && ch <= '9') var = var * 10 + ch - '0', ch = getchar();
    return var * f;
  }

  template <typename T>
  void write(T x) {
    static short int stack[40];
    if (x < 0) putchar('-'), x = -x;
    int top = 0;
    do stack[top++] = x % 10, x /= 10;
    while (x);
    while (top) putchar(stack[--top] + 48);
  }
}  // namespace FastIO
using namespace FastIO;

using PII = std::pair<int, int>;

constexpr int MAX_N = 2e5 + 5;
constexpr int MAX_M = 3e5 + 5;
constexpr int MAX_Q = 5e5 + 5;
constexpr int MAX_T = MAX_N + MAX_Q;

int N, M, Q, p[MAX_T];
std::vector<PII> e, q;

int fa[MAX_T];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

bool is_removed[MAX_M];
std::vector<std::vector<int>> g;

int dfn[MAX_T], ver[MAX_T], ts;
int size[MAX_T];

void DFS(int u) {
  size[ver[dfn[u] = ++ts] = u] = 1;
  for (int v : g[u]) DFS(v), size[u] += size[v];
}

struct SegT {
  struct Node {
    int val, id;
  } tr[MAX_T << 2];

  Node merge(const Node& L, const Node& R) { return L.val > R.val ? L : R; }

  void build(int u = 1, int nl = 1, int nr = N) {
    if (nl == nr) return tr[u] = {p[ver[nl]], nl}, void();
    int mid = (nl + nr) >> 1;
    build(u << 1, nl, mid);
    build(u << 1 | 1, mid + 1, nr);
    tr[u] = merge(tr[u << 1], tr[u << 1 | 1]);
  }

  void upd(int x, int u = 1, int nl = 1, int nr = N) {
    if (nl == nr) return tr[u].val = 0, void();
    int mid = (nl + nr) >> 1;
    if (x <= mid) upd(x, u << 1, nl, mid);
    else upd(x, u << 1 | 1, mid + 1, nr);
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
  N = read(), M = read(), Q = read();
  e.resize(M + 1), q.resize(Q + 1), g.resize(N + Q + 1);

  for (int i = 1; i <= N; ++i) p[i] = read();
  for (int i = 1; i <= M; ++i) e[i].first = read(), e[i].second = read();

  for (int i = 1; i <= Q; ++i) {
    q[i].first = read(), q[i].second = read();
    if (q[i].first == 2) is_removed[q[i].second] = true;  // 存储所有被第二种操作删除的边
  }

  std::iota(fa, fa + N + 1, 0);

  for (int i = 1, u, v; i <= M; ++i)
    if (!is_removed[i])  // 对于到最后都未被删除的边，直接合并其两个端点
      if ((u = find(e[i].first)) ^ (v = find(e[i].second)))
        fa[v] = u, g[u].push_back(v);  // 并在树上连一条边，注意合并方向与树上父子关系保持一致

  // 倒序处理所有操作
  for (int i = Q, u, v; i; --i) {
    if (q[i].first == 1)                // 对于查询操作
      q[i].second = find(q[i].second);  // 最终查询的范围为建出的树上表示该连通块的子树，于是存储当前状态下子树的根

    else if (q[i].first == 2)  // 对于删边操作，如果两端点还没有被合并
      if ((u = find(e[q[i].second].first)) ^ (v = find(e[q[i].second].second)))
        ++N, fa[u] = fa[v] = fa[N] = N,          // 用一个虚点作为这两个节点的父亲
          g[N].push_back(u), g[N].push_back(v);  // 以此连通这两个节点
  }

  // 预处理最终得到的树的 DFS 序
  for (int i = 1; i <= N; ++i)
    if (fa[i] == i)
      DFS(i);

  T.build();

  // 所有操作 2 已经转化为最终得到的树，对所有操作 1 处理询问并执行修改
  for (int i = 1, u; i <= Q; ++i)
    if (q[i].first == 1 && (u = q[i].second)) {
      auto [val, id] = T.qry(dfn[u], dfn[u] + size[u] - 1);
      T.upd(id), write(val), putchar('\n');
    }

  flush();
  return 0;
}
