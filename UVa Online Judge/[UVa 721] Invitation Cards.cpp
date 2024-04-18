#include <queue>
#include <cstdio>
#include <cstring>

using namespace std;

using PII = pair<int, int>;
const int N = 2e6 + 10;
const int INF = 0x3f3f3f3f;

int n, m, u, v, w, idx[2];
long long ans;
int ed[N][2], wt[N][2], nx[N][2], head[N][2], dist[N][2];
bool vis[N][2];

inline void add_edge(int u, int v, int w, int d) {
  ed[idx[d]][d] = v;
  wt[idx[d]][d] = w;
  nx[idx[d]][d] = head[u][d];
  head[u][d] = idx[d]++;
}

void Dijkstra(int st, int d) {
  for (int i = 1; i <= n; i++) {
    dist[i][d] = INF;
    vis[i][d] = 0;
  }
  dist[st][d] = 0;
  priority_queue<PII, vector<PII>, greater<PII>> heap;
  heap.emplace(dist[st][d], st);
  while (!heap.empty()) {
    int u = heap.top().second;
    heap.pop();
    if (vis[u][d])
      continue;
    vis[u][d] = 1;
    for (int i = head[u][d]; ~i; i = nx[i][d]) {
      int j = ed[i][d];
      if (dist[j][d] > dist[u][d] + wt[i][d]) {
        dist[j][d] = dist[u][d] + wt[i][d];
        heap.emplace(dist[j][d], j);
      }
    }
  }
}

void solve() {
  memset(head, -1, sizeof head);
  memset(idx, 0, sizeof idx);
  memset(ed, 0, sizeof ed);
  memset(wt, 0, sizeof wt);
  memset(nx, 0, sizeof nx);
  ans = 0;
  scanf("%d %d", &n, &m);
  while (m--) {
    scanf("%d %d %d", &u, &v, &w);
    add_edge(u, v, w, 0);
    add_edge(v, u, w, 1);
  }
  Dijkstra(1, 0);
  Dijkstra(1, 1);
  for (int i = 1; i <= n; i++)
    ans += dist[i][0] + dist[i][1];
  printf("%lld\n", ans);
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) solve();
  return 0;
}
