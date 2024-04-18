/*  由于 N,M <= 30，考虑暴搜；
    同时由于求的是状态之间的最短距离，可以考虑以状态为节点进行图论建模，并用最短路算法求解。

    由题可知，对于每一个华容道的局面，都只有两个可直接改变的元素：当前块的位置以及空白块的位置。
    显然，只有当前块与空白块相邻的情况是有意义的，所以选择用 (x, y, d) 进行状态表示，
    其中 (x, y) 为当前块的位置，(d) 为空白块相对于当前块的方向。
    只有当前块与空白块相邻的状态才需要考虑。

    考虑在以上状态表示方法下应该如何进行状态转移。
    显然，相邻两个状态（比如把空白从左边移动到右边）转移的权值不为 1，而是一个计算出来的距离。
    该距离可以通过事先对每一个方格进行状态转移的预处理来提前计算好，减小复杂度。*/

#include <queue>
#include <tuple>
#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;
using PII = pair<int, int>;
using STATE = tuple<int, int, int>;

const int N = 40;
const int VERT = N * N;
const int EDGE = 4 * VERT;
const int INF = 0x3F3F3F3F;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

int n, m, q;
bool b[N][N];
int tmp[N][N];         // tmp[x][y] 表示每次 BFS 从起点到 (x, y) 的最短路
int dist[N][N][4][4];  // dist[x][y][i][j] 表示将空白格从 (x, y) 的 i 方向转至 j 方向的最短距离

void BFS(int, int, int, int);
int SPFA(int, int, int, int, int, int);

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  memset(dist, 0x3F, sizeof dist);

  cin >> n >> m >> q;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      cin >> b[i][j];

  // 对相邻格子移动到相邻格子的状态转移的最短路径进行预处理
  for (int x = 1; x <= n; x++)
    for (int y = 1; y <= m; y++) {
      if (!b[x][y]) continue;
      for (int i = 0; i < 4; i++) {
        int tx = x + dx[i], ty = y + dy[i];
        if (!b[tx][ty]) continue;

        // 求从 (x, y) 相邻的某个方格开始，不经过 (x, y) 的情况下到达每一个方格的距离
        BFS(tx, ty, x, y);

        // 根据 BFS 结果更新 (x, y, i) --> (x, y, j) 转移的最短距离
        for (int j = 0; j < 4; j++) {
          int ttx = x + dx[j], tty = y + dy[j];
          if (!b[ttx][tty]) continue;
          dist[x][y][i][j] = tmp[ttx][tty];
        }
      }
    }

  while (q--) {
    int wx, wy, sx, sy, ex, ey;
    cin >> wx >> wy >> sx >> sy >> ex >> ey;
    cout << (sx == ex && sy == ey ? 0 : SPFA(wx, wy, sx, sy, ex, ey)) << endl;
  }

  fflush(stdout);
  return 0;
}

// 求从 (sx, sy) 相邻的某个方格开始，不经过 (ex, ey) 的情况下到达每一个方格的距离
void BFS(int sx, int sy, int ex, int ey) {
  memset(tmp, 0x3F, sizeof tmp);

  queue<PII> q;
  q.emplace(sx, sy);
  tmp[sx][sy] = 0;

  while (!q.empty()) {
    auto [x, y] = q.front();
    q.pop();

    for (int i = 0; i < 4; i++) {
      int tx = x + dx[i], ty = y + dy[i];

      if (tmp[tx][ty] < INF) continue;
      if (b[tx][ty] == false) continue;
      if (tx == ex && ty == ey) continue;

      tmp[tx][ty] = tmp[x][y] + 1;
      q.emplace(tx, ty);
    }
  }
}

int path_len[N][N][4];
bool vis[N][N][4];

int SPFA(int wx, int wy, int sx, int sy, int ex, int ey) {
  memset(path_len, 0x3F, sizeof path_len);
  memset(vis, 0, sizeof vis);

  BFS(wx, wy, sx, sy);  // 暴搜空白格移动到矩阵内所有格子的最短距离

  queue<STATE> q;

  // 初始化队列，先填入基于 (sx, sy) 四个方向上所有可能的状态转移
  for (int i = 0; i < 4; i++) {
    int tx = sx + dx[i], ty = sy + dy[i];
    if (tmp[tx][ty] == INF) continue;

    vis[sx][sy][i] = true;
    path_len[sx][sy][i] = tmp[tx][ty];
    q.emplace(sx, sy, i);
  }

  while (!q.empty()) {
    auto [x, y, d] = q.front();
    q.pop();

    vis[x][y][d] = false;

    for (int i = 0; i < 4; i++) {
      int tx = x + dx[i], ty = y + dy[i];
      int w = dist[x][y][i][d] + 1;

      int rev = (i + 2) % 4;  // 取当前空白格所在方向的反方向

      /*  空白格所在方向的反方向就是可移动方格相对于 (ex, ey) 目标的方向
          所以需要把空白格交换到当前它相对于可移动方格方向的反方向
          也就是把可移动方格朝目标 (ex, ey) 移动，最终到达终点 */

      if (path_len[tx][ty][rev] > path_len[x][y][d] + w) {
        path_len[tx][ty][rev] = path_len[x][y][d] + w;  // 更新最短路
        if (!vis[tx][ty][rev])
          q.emplace(tx, ty, rev), vis[tx][ty][rev] = true;
      }
    }
  }

  int ans = INF;
  for (int i = 0; i < 4; i++)
    ans = min(ans, path_len[ex][ey][i]);

  return (ans == INF ? -1 : ans);
}
