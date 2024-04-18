#include <queue>
#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e5 + 10;
const int M = 4e5 + 10;
const int MOD = 1e5 + 3;

int n, m;
int ed[M], nx[M], head[N], idx;
int dist[N], cnt[N];

void connect(int u, int v) {
  ed[idx] = v;
  nx[idx] = head[u];
  head[u] = idx++;
}

void BFS(int u) {
  memset(dist, 0x7F, sizeof dist);
  queue<int> q;

  q.push(u);
  dist[u] = 0;
  cnt[u] = 1;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int i = head[u]; ~i; i = nx[i]) {
      int v = ed[i];
      if (dist[v] > dist[u] + 1) {
        dist[v] = dist[u] + 1;
        cnt[v] = cnt[u];
        q.push(v);
      } else if (dist[v] == dist[u] + 1)
        cnt[v] = (cnt[v] + cnt[u]) % MOD;
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  memset(head, -1, sizeof head);

  cin >> n >> m;

  while (m--) {
    int u, v;
    cin >> u >> v;
    connect(u, v), connect(v, u);
  }

  BFS(1);

  for (int i = 1; i <= n; i++)
    cout << cnt[i] << endl;
  fflush(stdout);
  return 0;
}
