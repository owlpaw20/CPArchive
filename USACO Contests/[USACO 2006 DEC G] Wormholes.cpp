#include <queue>
#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 5e2 + 5;
const int M = 5.2e3 + 5;

int n, m, p;
int ed[M], nx[M], wt[M], head[N], idx;
int dist[N], cnt[N];
bool vis[N];

void connect(int u, int v, int w) {
  ed[idx] = v;
  wt[idx] = w;
  nx[idx] = head[u];
  head[u] = idx++;
}

bool SPFA() {
  memset(dist, 0, sizeof dist);
  memset(cnt, 0, sizeof cnt);
  memset(vis, 0, sizeof vis);

  queue<int> q;

  for (int i = 1; i <= n; i++)
    q.push(i), vis[i] = true;  // 把所有点都遍历到，确保能找到负环

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    vis[u] = false;

    for (int i = head[u]; ~i; i = nx[i]) {
      int v = ed[i], w = wt[i];
      if (dist[v] > dist[u] + w) {
        dist[v] = dist[u] + w;
        cnt[v] = cnt[u] + 1;
        if (cnt[v] >= n)  // 如果路径上出现了一个环且其中出现一个重复遍历的节点
          return true;    // 说明这个节点绕环一圈更新了自己的最短距离，故环总长度为负
        if (!vis[v]) {
          q.push(v);
          vis[v] = true;
        }
      }
    }
  }

  return false;
}

void solve() {
  memset(head, -1, sizeof head);
  idx = 0;

  cin >> n >> m >> p;

  while (m--) {
    int u, v, w;
    cin >> u >> v >> w;
    connect(u, v, w);
    connect(v, u, w);
  }

  while (p--) {
    int u, v, w;
    cin >> u >> v >> w;
    connect(u, v, -w);
  }

  puts(SPFA() ? "YES" : "NO");
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while (T--) solve();

  fflush(stdout);
  return 0;
}
