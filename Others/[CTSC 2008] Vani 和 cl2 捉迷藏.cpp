#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 2e2 + 5;

int n, m;
bool vis[N];
int match[N];
bool g[N][N];

bool Hungarian(int u) {
  for (int v = 1; v <= n; v++)
    if (!vis[v] && g[u][v]) {
      vis[v] = true;
      if (!match[v] || Hungarian(match[v]))
        return match[v] = u, true;
    }
  return false;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;

  while (m--) {
    int u, v;
    cin >> u >> v;
    g[u][v] = true;
  }

  for (int w = 1; w <= n; w++)
    for (int u = 1; u <= n; u++)
      for (int v = 1; v <= n; v++)
        g[u][v] |= g[u][w] & g[w][v];

  int ans = 0;
  for (int i = 1; i <= n; i++)
    memset(vis, 0, sizeof vis), ans += Hungarian(i);

  cout << n - ans << endl;
  fflush(stdout);
  return 0;
}
