#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;
using VI = vector<int>;
using PII = pair<int, int>;

const int N = 5e4 + 10;
const int INF = 0x3F3F3F3F;

int n, m;
vector<PII> G[N];
vector<int> via(5);
vector<VI> dist(5, VI(N, INF));
unordered_map<int, int> idx;

void Dijkstra(int st, int id) {
  vector<bool> vis(N);
  priority_queue<PII, vector<PII>, greater<PII>> heap;
  heap.emplace(dist[id][st] = 0, st);
  while (!heap.empty()) {
    int u = heap.top().second;
    heap.pop();
    if (vis[u]) continue;
    vis[u] = true;
    for (PII ver : G[u]) {
      int v = ver.first, w = ver.second;
      if (dist[id][v] > dist[id][u] + w)
        heap.emplace(dist[id][v] = dist[id][u] + w, v);
    }
  }
}

int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  cin >> n >> m;
  for (int i = 0; i < 5; i++) cin >> via[i];
  sort(via.begin(), via.end());
  for (int i = 0; i < 5; i++) idx[via[i]] = i;
  while (m--) {
    int u, v, w;
    cin >> u >> v >> w;
    G[u].emplace_back(v, w);
    G[v].emplace_back(u, w);
  }
  for (int i = 0; i < 5; i++) Dijkstra(via[i], i);
  int ans = INF;
  do {
    int d = dist[idx[via[0]]][1];
    for (int i = 0; i < 4; i++)
      d += dist[idx[via[i]]][via[i + 1]];
    ans = min(ans, d);
  } while (next_permutation(via.begin(), via.end()));
  cout << ans << endl;
  return 0;
}
