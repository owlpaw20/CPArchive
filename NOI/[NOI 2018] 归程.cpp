#include <queue>
#include <cstring>
#include <numeric>
#include <iostream>
#include <algorithm>

namespace FastIO {
  const int MAX_BUF = 1 << 20;
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
    static int stack[40];
    if (x < 0) putchar('-'), x = -x;
    int top = 0;
    do stack[top++] = x % 10, x /= 10;
    while (x);
    while (top) putchar(stack[--top] + 48);
  }
}  // namespace FastIO
using namespace FastIO;

using PII = std::pair<int, int>;

const int MAX_N = 8e5 + 5;
const int MAX_M = MAX_N * 2;

int N, M;
int head[MAX_N], ed[MAX_M], wt[MAX_M], nx[MAX_M], idx;

// ---------- Dijkstra 部分 ----------

void connect(int u, int v, int w) {
  ed[idx] = v;
  wt[idx] = w;
  nx[idx] = head[u];
  head[u] = idx++;
}

int dist[MAX_N];
bool vis[MAX_N];

void Dijkstra(int st = 1) {
  memset(dist, 0x3F, sizeof(int) * (N * 2 + 1));
  memset(vis, 0, sizeof(int) * (N + 1));

  std::priority_queue<PII, std::vector<PII>, std::greater<PII>> heap;
  heap.emplace(dist[st] = 0, st);

  while (!heap.empty()) {
    int u = heap.top().second;
    heap.pop();

    if (vis[u]) continue;
    vis[u] = true;

    for (int i = head[u], v; ~i; i = nx[i])
      if (dist[v = ed[i]] > dist[u] + wt[i])
        heap.emplace(dist[v] = dist[u] + wt[i], v);
  }
}

// ---------- Kruskal 部分 ----------

struct Edge {
  int u, v, w, a;
} edge[MAX_M];

struct UnionFind {
  int fa[MAX_N];
  void init(int x) { std::iota(fa, fa + x + 1, 0); }
  int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
} set;

void connect(int u, int v) {
  ed[idx] = v;
  nx[idx] = head[u];
  head[u] = idx++;
}

int cnt;
int ver_w[MAX_N];

void Kruskal() {
  memset(head, -1, sizeof(int) * (N * 2 + 1));
  memset(ver_w, 0, sizeof(int) * (N * 2 + 1));
  set.init(N * 2);
  idx = 0;

  auto cmp = [&](const Edge& x, const Edge& y) { return x.a > y.a; };
  std::sort(edge + 1, edge + M + 1, cmp);

  cnt = N;
  for (int i = 1, u, v; i <= M; ++i) {
    u = set.find(edge[i].u);
    v = set.find(edge[i].v);
    if (u != v) {
      ver_w[++cnt] = edge[i].a;
      set.fa[u] = set.fa[v] = cnt;
      connect(cnt, u), connect(cnt, v);
    }
    if (cnt == N * 2 - 1) break;
  }
}

// ---------- 树上倍增部分 ----------

int fa[MAX_N][20];
int depth[MAX_N];

void BFS() {
  memset(fa, 0, sizeof(int) * (N * 2 + 1) * 20);
  memset(depth, 0, sizeof(int) * (N * 2 + 1));
  depth[cnt] = 1;

  std::queue<int> q;
  q.push(cnt);

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int i = head[u], v; ~i; i = nx[i])
      if (!depth[v = ed[i]]) {
        fa[v][0] = u;
        depth[v] = depth[u] + 1;
        for (int i = 1; i <= 19; ++i)
          fa[v][i] = fa[fa[v][i - 1]][i - 1];
        q.push(v);
      }
  }
}

int DFS(int u) {
  for (int i = head[u]; ~i; i = nx[i])
    dist[u] = std::min(dist[u], DFS(ed[i]));
  return dist[u];
}

void solve() {
  N = read(), M = read();
  memset(head, -1, sizeof(int) * (N + 1));

  for (int i = 1, u, v, w; i <= M; ++i) {
    edge[i] = (Edge){u = read(), v = read(), w = read(), read()};
    connect(u, v, w), connect(v, u, w);
  }

  Dijkstra();
  Kruskal();
  BFS();
  DFS(cnt);

  static int q, k, s, lastans;
  q = read(), k = read(), s = read();
  lastans = 0;

  while (q--) {
    static int v, p;
    v = read(), p = read();

    v = (v + k * lastans - 1) % N + 1;
    p = (p + k * lastans) % (s + 1);

    for (int i = 19; ~i; --i)
      if (ver_w[fa[v][i]] > p)
        v = fa[v][i];

    write(lastans = dist[v]), putchar('\n');
  }
}

int main() {
  int T = read();
  while (T--) solve();
  return flush(), 0;
}
