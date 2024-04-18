#pragma GCC optimize("O2,unroll-loops")
#include <cstring>
#include <iostream>
#define endl '\n'

using namespace std;

const int N = 1e2 + 10;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

int T;
char g[N][N];
bool vis[N][N];

bool DFS(int x, int y, int ex, int ey, int n) {
  if (x == ex && y == ey) return true;
  for (int i = 0; i < 4; i++) {
    int tx = x + dx[i], ty = y + dy[i];
    if (tx < 0 || ty < 0 || tx >= n || ty >= n) continue;
    if (vis[tx][ty] == true || g[tx][ty] == '#') continue;
    vis[tx][ty] = true;
    if (DFS(tx, ty, ex, ey, n)) return true;
  }
  return false;
}

void solve() {
  memset(g, 0, sizeof g);
  memset(vis, false, sizeof vis);

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> g[i];

  int sx, sy, ex, ey;
  cin >> sx >> sy >> ex >> ey;
  if (g[sx][sy] == '#' || g[ex][ey] == '#')
    return (void)(cout << "NO" << endl);

  vis[sx][sy] = true;
  cout << (DFS(sx, sy, ex, ey, n) ? "YES" : "NO") << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> T;
  while (T--) solve();

  fflush(stdout);
  return 0;
}
