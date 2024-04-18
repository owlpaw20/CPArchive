#include <cstring>
#include <iostream>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using PII = pair<int, int>;

const int N = 1e3 + 10;
const int M = 2e4 + 10;

int n, m, K, idx, hd[N];
int ed[M], nx[M], wt[M];
int dist[N];
bool vis[N];

__gnu_pbds::priority_queue<PII, greater<PII>> heap;

void connect(int u, int v, int w) {
  ed[idx] = v;
  wt[idx] = w;
  nx[idx] = hd[u];
  hd[u] = idx++;
}

bool check(int limit, int st = 1) {
  memset(dist, 0x3F, sizeof dist);
  memset(vis, false, sizeof vis);
  heap.push({dist[st] = 0, st});
  while (!heap.empty()) {
    int u = heap.top().second;
    heap.pop();
    if (vis[u]) continue;
    vis[u] = true;
    for (int i = hd[u]; ~i; i = nx[i]) {
      int j = ed[i], flag = wt[i] > limit;
      if (dist[j] > dist[u] + flag)
        heap.push({dist[j] = dist[u] + flag, j});
    }
  }
  return dist[n] <= K;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  memset(hd, -1, sizeof hd);

  cin >> n >> m >> K;

  while (m--) {
    int u, v, w;
    cin >> u >> v >> w;
    connect(u, v, w);
    connect(v, u, w);
  }

  int l = 0, r = 1e6 + 1;
  while (l < r) {
    int mid = (l + r) >> 1;
    if (check(mid))
      r = mid;
    else
      l = mid + 1;
  }

  if (r > 1e6) r = -1;
  cout << r << endl;
  return 0;
}
