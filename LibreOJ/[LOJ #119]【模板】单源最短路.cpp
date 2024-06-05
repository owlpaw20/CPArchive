#include <queue>
#include <vector>
#include <iostream>

#define endl '\n'

using l64 = long long;
using PII = std::pair<int, int>;
using PLI = std::pair<l64, int>;

const l64 INF = 1e18;

int N, M;
std::vector<l64> sp;
std::vector<bool> vis;
std::vector<std::vector<PII>> adj;

l64 Dijkstra(int st, int fn) {
  std::priority_queue<PLI, std::vector<PLI>, std::greater<PLI>> heap;
  heap.emplace(sp[st] = 0, st);

  while (!heap.empty()) {
    auto [d, u] = heap.top();
    heap.pop();

    if (vis[u]) continue;
    vis[u] = true;

    for (auto [v, w] : adj[u])
      if (sp[v] > sp[u] + w)
        sp[v] = sp[u] + w, heap.emplace(sp[v], v);
  }

  return sp[fn];
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int s, t;

  std::cin >> N >> M >> s >> t;
  adj.resize(N + 1), sp.assign(N + 1, INF), vis.resize(N + 1);

  for (int i = 1, u, v, w; i <= M; ++i) {
    std::cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }

  std::cout << Dijkstra(s, t) << endl;
  return fflush(stdout), 0;
}
