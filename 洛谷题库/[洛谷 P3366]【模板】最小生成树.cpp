#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 5e3 + 10;
const int INF = 0x3f3f3f3f;

int n, m, g[N][N], dist[N];
bool vis[N];

int Prim() {
  memset(dist, 0x3f, sizeof dist);
  int res = 0;
  for (int i = 1; i <= n; i++) {
    int t = -1;
    for (int j = 1; j <= n; j++)
      if (!vis[j] && (t == -1 || dist[t] > dist[j]))
        t = j;
    if (i != 1 && dist[t] == INF)
      return INF;
    if (i != 1) res += dist[t];
    vis[t] = 1;
    for (int j = 1; j <= n; j++)
      dist[j] = min(dist[j], g[t][j]);
  }
  return res;
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> n >> m;
  memset(g, 0x3f, sizeof g);
  while (m--) {
    int u, v, w;
    cin >> u >> v >> w;
    g[u][v] = g[v][u] = min(g[u][v], w);
  }
  int res = Prim();
  if (res == INF)
    puts("orz");
  else
    cout << res << endl;
  return 0;
}
