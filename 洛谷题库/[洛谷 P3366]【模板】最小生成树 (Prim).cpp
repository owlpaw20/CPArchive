#include <queue>
#include <cstring>
#include <iostream>

using PII = std::pair<int, int>;

const int MAX_N = 5e3 + 5;
const int MAX_M = 4e5 + 5;

int N, M;
int ed[MAX_M], nx[MAX_M], wt[MAX_M], head[MAX_N], idx;

void connect(int u, int v, int w) {
  ed[idx] = v;
  wt[idx] = w;
  nx[idx] = head[u];
  head[u] = idx++;
}

int dist[MAX_N];

int Prim(int st = 1) {
  static bool vis[MAX_N];

  memset(dist, 0x3F, sizeof(int) * (N + 1));
  memset(vis, 0, sizeof(bool) * (N + 1));

  int cnt = 0, ret = 0;

  std::priority_queue<PII, std::vector<PII>, std::greater<PII>> heap;
  heap.emplace(dist[st] = 0, st);

  while (!heap.empty() && cnt < N) {
    auto [d, u] = heap.top();
    heap.pop();

    if (vis[u]) continue;
    vis[u] = true;

    ret += d, ++cnt;

    for (int i = head[u], v; ~i; i = nx[i])
      if (wt[i] < dist[v = ed[i]])
        heap.emplace(dist[v] = wt[i], v);
  }

  return (cnt == N) ? ret : -1;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;
  memset(head, -1, sizeof(int) * (N + 1));

  while (M--) {
    static int u, v, w;
    std::cin >> u >> v >> w;
    connect(u, v, w), connect(v, u, w);
  }

  int ans = Prim();
  std::cout << (ans == -1 ? "orz" : std::to_string(ans)) << std::endl;

  return 0;
}
