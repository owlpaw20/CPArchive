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
  int x, y, curr, color;
  Node(int _x, int _y, int _curr, int _color) : x(_x), y(_y), curr(_curr), color(_color) {}
  bool operator<(const Node &t) const {
    return curr > t.curr;
  }
};

void Dijkstra(int sx, int sy) {
  memset(dist, 0x3F, sizeof dist);

  dist[sx][sy][g[sx][sy]] = 0;
  priority_queue<Node> heap;
  heap.emplace(sx, sy, dist[sx][sy][g[sx][sy]], g[sx][sy]);

  while (!heap.empty()) {
    Node u = heap.top();
    heap.pop();

    int x = u.x, y = u.y, color = u.color;

    if (vis[x][y][color]) continue;
    vis[x][y][color] = true;

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
          heap.emplace(tx, ty, dist[tx][ty][tc], tc);
        }
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  memset(g, -1, sizeof g);

  cin >> n >> m;
  while (m--) {
    int x, y, c;
    cin >> x >> y >> c;
    g[x][y] = c;
  }

  Dijkstra(1, 1);

  int ans = min(dist[n][n][0], dist[n][n][1]);
  if (ans == INF)
    cout << -1 << endl;
  else
    cout << ans << endl;
  return 0;
}