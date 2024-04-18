#include <queue>
#include <cstring>
#include <iostream>
using namespace std;

const int SIZE = 1e2 + 10;
const int INF = 0x3F3F3F3F;
const int DX[] = {0, 1, 0, -1};
const int DY[] = {1, 0, -1, 0};

int n, m;
int g[SIZE][SIZE];  // 邻接数组存图
int dist[SIZE][SIZE][2];
bool vis[SIZE][SIZE][2];

struct Node {
  int x, y, color;
  Node(int _x, int _y, int _color) : x(_x), y(_y), color(_color) {}
};

int SPFA(int sx, int sy) {
  memset(dist, 0x3F, sizeof dist);
  dist[sx][sy][g[sx][sy]] = 0;
  queue<Node> q;
  q.emplace(sx, sy, g[sx][sy]);
  while (!q.empty()) {
    Node u = q.front();
    q.pop();
    int x = u.x, y = u.y, color = u.color;
    vis[x][y][color] = false;
    for (int i = 0; i < 4; i++) {
      int tx = x + DX[i], ty = y + DY[i];
      if (tx > 0 && ty > 0 && tx <= n && ty <= n) {
        int cur = g[x][y], nxt = g[tx][ty];
        int delta = 0, tc = 0;
        if (nxt != -1) {  // 如果目标点有色
          if (color == nxt)
            delta = 0;
          else
            delta = 1;
          tc = nxt;
        } else if (cur != -1) {  // 如果当前点有色、目标点无色
          delta = 2;
          tc = cur;
        } else
          continue;
        if (dist[tx][ty][tc] > dist[x][y][color] + delta) {
          dist[tx][ty][tc] = dist[x][y][color] + delta;
          if (!vis[tx][ty][tc])
            q.emplace(tx, ty, tc), vis[tx][ty][tc] = true;
        }
      }
    }
  }
  return min(dist[n][n][0], dist[n][n][1]);
}

int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  memset(g, -1, sizeof g);
  cin >> n >> m;
  while (m--) {
    int x, y, c;
    cin >> x >> y >> c;
    g[x][y] = c;
  }
  int ans = SPFA(1, 1);
  if (ans == INF)
    cout << -1 << endl;
  else
    cout << ans << endl;
  return 0;
}
