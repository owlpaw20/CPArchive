#include <bits/stdc++.h>

namespace FastIO {
  const int MAX_BUF = 1 << 16;
  char buf[MAX_BUF], *p1, *p2;

  inline char getchar() { return (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAX_BUF, stdin), p1 == p2) ? EOF : *p1++); }

  template <typename T>
  T read() {
    uint8_t f = 1;
    T var = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
      if (ch == '-') f = -f;
      ch = getchar();
    }
    while (ch >= '0' && ch <= '9') var = var * 10 + ch - '0', ch = getchar();
    return var * f;
  }
}  // namespace FastIO
using namespace FastIO;

using PII = std::pair<int, int>;
using TUP = std::tuple<int, int, int>;

const int MAX_N = 2e3 + 5;

int N, d[MAX_N][MAX_N];
std::vector<TUP> edges;

int fa[MAX_N];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

std::vector<std::vector<PII>> adj;

void Kruskal() {
  std::sort(edges.begin(), edges.end());
  std::iota(fa, fa + N + 1, 0);

  int cnt = 0;

  for (auto [w, u, v] : edges) {
    int fu = find(u), fv = find(v);
    if (cnt == N - 1) break;
    if (fu != fv) {
      fa[fu] = fv, ++cnt;
      adj[u].emplace_back(v, w);
      adj[v].emplace_back(u, w);
    }
  }
}

int dist[MAX_N];

void DFS(int u, int f = -1) {
  for (auto [v, w] : adj[u])
    if (v != f)
      dist[v] = dist[u] + w, DFS(v, u);
}

int main() {
  N = read<int>();

  for (int i = 1; i <= N; ++i)
    for (int j = 1; j <= N; ++j)
      d[i][j] = read<int>();

  for (int i = 1; i <= N; ++i)
    for (int j = 1; j < i; ++j)
      if (d[i][i] || !d[i][j] || d[i][j] != d[j][i])
        goto fail;

  edges.reserve(N * N / 2);
  adj.resize(N + 1);

  for (int i = 1; i <= N; ++i)
    for (int j = 1; j < i; ++j)
      edges.emplace_back(d[j][i], j, i);

  Kruskal();

  for (int i = 1; i <= N ? dist[i] = 0, DFS(i), true : false; ++i)
    for (int j = 1; j <= N; ++j)
      if (dist[j] != d[i][j])
        goto fail;

  puts("YES");
  return 0;

fail:
  puts("NO");
  return 0;
}
