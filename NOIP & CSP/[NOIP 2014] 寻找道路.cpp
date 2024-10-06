#include <bits/stdc++.h>

const int MAX_N = 1e4 + 5;
const int INF = 0x3F3F3F3F;

int N, M, S, T;
std::vector<std::vector<int>> g, h;

bool reach[MAX_N], flag[MAX_N];

void DFS(int u) {
  reach[u] = true;
  for (int v : h[u])
    if (!reach[v]) DFS(v);
}

bool vis[MAX_N];
int dist[MAX_N];

void Dijkstra(int st) {
  using PII = std::pair<int, int>;
  memset(dist, 0x3F, sizeof(int) * (N + 1));

  std::priority_queue<PII, std::vector<PII>, std::greater<PII>> heap;
  heap.emplace(dist[st] = 0, st);

  while (!heap.empty()) {
    int u = heap.top().second;
    heap.pop();

    if (vis[u] || !flag[u]) continue;
    vis[u] = true;

    for (int v : g[u])
      if (flag[v] && !vis[v] && dist[v] > dist[u] + 1)
        heap.emplace(dist[v] = dist[u] + 1, v);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;
  g.resize(N + 1), h.resize(N + 1);

  while (M--) {
    static int u, v;
    std::cin >> u >> v;
    g[u].push_back(v);
    h[v].push_back(u);
  }

  std::cin >> S >> T;

  DFS(T);

  for (int i = 1; i <= N; ++i) {
    flag[i] = reach[i];
    for (int v : g[i]) flag[i] &= reach[v];
  }

  Dijkstra(S);

  std::cout << (dist[T] == INF ? -1 : dist[T]) << std::flush;
  return 0;
}
