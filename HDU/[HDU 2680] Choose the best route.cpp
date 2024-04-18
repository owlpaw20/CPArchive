#pragma GCC optimize("O2")

#include <queue>
#include <vector>
#include <iostream>

#define endl '\n'

using namespace std;
using PII = pair<int, int>;

const int N = 1e3 + 10;
const int INF = 0x3F3F3F3F;

int n, m, s, W;
vector<PII> G[N];
vector<int> dist;

void Dijkstra(int st) {
  vector<bool> vis(n + 10, false);
  priority_queue<PII, vector<PII>, greater<PII>> heap;
  heap.emplace(dist[st] = 0, st);
  while (!heap.empty()) {
    int u = heap.top().second;
    heap.pop();
    if (vis[u]) continue;
    vis[u] = true;
    for (auto [v, w] : G[u])
      if (dist[v] > dist[u] + w)
        heap.emplace(dist[v] = dist[u] + w, v);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  while (cin >> n >> m >> s) {
    dist.assign(n + 10, INF);
    for (int i = 1; i <= n; i++) G[i].clear();

    while (m--) {
      int u, v, w;
      cin >> u >> v >> w;
      G[v].emplace_back(u, w);
    }

    Dijkstra(s);

    cin >> W;
    int ans = INF;
    while (W--) {
      int t;
      cin >> t;
      ans = min(ans, dist[t]);
    }

    cout << (ans == INF ? -1 : ans) << endl;
  }

  fflush(stdout);
  return 0;
}
