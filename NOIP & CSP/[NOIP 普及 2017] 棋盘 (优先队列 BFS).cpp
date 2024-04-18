#include <queue>
#include <cstring>
#include <iostream>
using namespace std;

const int SIZE = 1e2 + 10;
const int INF = 0x3F3F3F3F;
const int DX[] = {0, 1, 0, -1};
const int DY[] = {1, 0, -1, 0};

int n, m, minn = INF;
int g[SIZE][SIZE];  // 0 = 无色, 1 = 红色, 2 = 黄色
int cost[SIZE][SIZE];

struct Node {
  int x, y, curr, color;
  Node(int a, int b, int c, int d) : x(a), y(b), curr(c), color(d) {}
  bool operator<(const Node &t) const {
    return curr > t.curr;
  }
};

void BFS(int sx, int sy) {
  priority_queue<Node> q;
  q.emplace(sx, sy, 0, g[sx][sy]);
  while (!q.empty()) {
    Node u = q.top();
    q.pop();
    int x = u.x, y = u.y, curr = u.curr, color = u.color;
    if (x == n && y == n) {
      minn = min(minn, curr);
      continue;
    }
    for (int i = 0; i < 4; i++) {
      int tx = x + DX[i], ty = y + DY[i];
      if (tx > 0 && ty > 0 && tx <= n && ty <= n) {
        if (g[x][y] == 0 && g[tx][ty] == 0) continue;  // 魔法不能连续使用
        if (g[tx][ty] == 0) {                          // 如果目标点无色
          if (curr + 2 < cost[tx][ty]) {
            cost[tx][ty] = curr + 2;
            q.emplace(tx, ty, curr + 2, color);
          }
        } else {  // 如果目标点有色
          if (color == g[tx][ty] && curr < cost[tx][ty]) {
            cost[tx][ty] = curr;
            q.emplace(tx, ty, curr, color);
          } else if (curr + 1 < cost[tx][ty]) {
            cost[tx][ty] = curr + 1;
            q.emplace(tx, ty, curr + 1, g[tx][ty]);
          }
        }
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  memset(cost, 0x3F, sizeof cost);
  cin >> n >> m;
  while (m--) {
    int x, y, c;
    cin >> x >> y >> c;
    g[x][y] = c + 1;
  }
  BFS(1, 1);
  if (minn == INF)
    cout << -1 << endl;
  else
    cout << minn << endl;
  return 0;
}
