#include <queue>
#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;
using PII = pair<int, int>;

const int N = 5e3 + 10;
const int M = 2e5 + 10;
const int INF = 0x7FFFFFFF;

int n, m;
int dist[N], scnd[N];
int ed[M], nx[M], wt[M], head[N], idx;

void connect(int u, int v, int w) {
  ed[idx] = v;
  wt[idx] = w;
  nx[idx] = head[u];
  head[u] = idx++;
}

void Dijkstra(int st = 1) {
  memset(dist, 0x3F, sizeof dist);
  memset(scnd, 0x3F, sizeof scnd);

  priority_queue<PII, vector<PII>, greater<PII>> heap;
  heap.emplace(dist[st] = 0, st);

  while (!heap.empty()) {
    auto [d, u] = heap.top();
    heap.pop();

    for (int i = head[u]; ~i; i = nx[i]) {
      int v = ed[i], w = wt[i];
      if (dist[v] > d + w) {
        heap.emplace(scnd[v] = dist[v], v);
        heap.emplace(dist[v] = d + w, v);
      } else if (scnd[v] > d + w)
        heap.emplace(scnd[v] = d + w, v);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  memset(head, -1, sizeof head);

  cin >> n >> m;

  while (m--) {
    int u, v, w;
    cin >> u >> v >> w;
    connect(u, v, w);
    connect(v, u, w);
  }

  Dijkstra();

  cout << scnd[n] << endl;
  fflush(stdout);
  return 0;
}
