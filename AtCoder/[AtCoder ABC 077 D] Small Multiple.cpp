#include <queue>
#include <cstring>
#include <iostream>

using PII = std::pair<int, int>;

constexpr int MAX_N = 1e5 + 5;
constexpr int MAX_M = MAX_N * 20;

int N;
int ed[MAX_M], nx[MAX_M], wt[MAX_M], head[MAX_N], idx;

void connect(int u, int v, int w) { ed[idx] = v, wt[idx] = w, nx[idx] = head[u], head[u] = idx++; }

int Dijkstra(int st = 1, int fn = 0) {
  static int dist[MAX_N];
  static bool vis[MAX_N];

  memset(dist, 0x3F, sizeof(int) * (N + 1));
  memset(vis, 0, sizeof(bool) * (N + 1));

  std::priority_queue<PII, std::vector<PII>, std::greater<PII>> heap;
  heap.emplace(dist[st] = 1, st);

  while (!heap.empty()) {
    auto [d, u] = heap.top();
    heap.pop();

    if (vis[u]) continue;
    vis[u] = true;

    for (int i = head[u], v; ~i; i = nx[i])
      if (dist[v = ed[i]] > dist[u] + wt[i])
        heap.emplace(dist[v] = dist[u] + wt[i], v);
  }

  return dist[fn];
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  memset(head, -1, sizeof(int) * (N + 1));

  for (int i = 0; i < N; ++i) {
    connect(i, (i + 1) % N, 1);
    connect(i, 10 * i % N, 0);
  }

  std::cout << Dijkstra() << std::endl;
  return 0;
}
