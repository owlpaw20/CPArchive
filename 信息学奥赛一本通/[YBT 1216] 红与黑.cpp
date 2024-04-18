#pragma GCC optimize("O2,unroll-loops")
#include <queue>
#include <cstring>
#include <iostream>
#define endl '\n'

using namespace std;
using PII = pair<int, int>;

const int N = 30;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

int n, m, sx, sy;
char g[N][N];
bool vis[N][N];

void BFS(int sx, int sy) {
  vis[sx][sy] = true;
  queue<PII> q;
  q.emplace(sx, sy);

  while (!q.empty()) {
    auto [x, y] = q.front();
    q.pop();

    for (int i = 0; i < 4; i++) {
      int tx = x + dx[i], ty = y + dy[i];
      if (tx < 1 || ty < 1 || tx > n || ty > m) continue;
      if (vis[tx][ty] || g[tx][ty] == '#') continue;
      vis[tx][ty] = true;
      q.emplace(tx, ty);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  while (cin >> n >> m, n && m) {
    swap(n, m);
    memset(g, 0, sizeof g);
    memset(vis, false, sizeof vis);

    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++) {
        cin >> g[i][j];
        if (g[i][j] == '@')
          sx = i, sy = j, g[i][j] = '.';
      };

    BFS(sx, sy);

    int ans = 0;
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++)
        if (vis[i][j])
          ans += 1;

    cout << ans << endl;
  }

  fflush(stdout);
  return 0;
}
