#include <bits/stdc++.h>

const int MAX_N = 1e3 + 5;
const int MAX_M = 1e5 + 5;

int N, M;
int head[MAX_N], ed[MAX_M], nx[MAX_M], wt[MAX_M], idx;
void connect(int u, int v, int w) { ed[++idx] = v, wt[idx] = w, nx[idx] = head[u], head[u] = idx; }

struct Edge {
  int u, v, w;
  bool operator<(const Edge& t) const { return w < t.w; }
} edge[MAX_M];

int fa[MAX_N];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

void Kruskal() {
  std::iota(fa, fa + N + 1, 0);
  std::sort(edge + 1, edge + M + 1);
  for (int i = 1, cnt = 0; i <= M; ++i) {
    int u = find(edge[i].u), v = find(edge[i].v);
    if (u != v) {
      connect(u, v, edge[i].w);
      connect(v, u, edge[i].w);
      fa[u] = v, ++cnt;
    }
    if (cnt == N - 1) break;
  }
}

int dep[MAX_N];
int anc[MAX_N][20];
int maxW[MAX_N][20];

void DFS(int u) {
  dep[u] = dep[anc[u][0]] + 1;

  for (int i = head[u], v; ~i; i = nx[i]) {
    if (dep[v = ed[i]]) continue;

    anc[v][0] = u;
    maxW[v][0] = wt[i];

    for (int j = 1; j < 20; ++j) {
      anc[v][j] = anc[anc[v][j - 1]][j - 1];
      maxW[v][j] = std::max(maxW[v][j - 1], maxW[anc[v][j - 1]][j - 1]);
    }

    DFS(v);
  }
}

int qry(int S, int T) {
  if (find(S) != find(T)) return -1;
  if (dep[S] > dep[T]) std::swap(S, T);

  int ret = 0;

  for (int i = 19; ~i; --i)
    if (dep[anc[T][i]] >= dep[S])
      ret = std::max(ret, maxW[T][i]), T = anc[T][i];

  if (S == T) return ret;

  for (int i = 19; ~i; --i)
    if (anc[S][i] != anc[T][i])
      ret = std::max({ret, maxW[S][i], maxW[T][i]}), S = anc[S][i], T = anc[T][i];

  return std::max({ret, maxW[S][0], maxW[T][0]});
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int k;
  std::cin >> N >> M >> k;
  memset(head, -1, 4 * (N + 1));
  for (int i = 1, u, v, w; i <= M; ++i) std::cin >> u >> v >> w, edge[i] = {u, v, w};

  Kruskal();

  for (int i = 1; i <= N; ++i)
    if (!dep[i])
      DFS(i);

  while (k--) {
    static int S, T;
    std::cin >> S >> T;
    std::cout << qry(S, T) << '\n';
  }

  std::cout.flush();
  return 0;
}
