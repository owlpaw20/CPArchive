#include <deque>
#include <tuple>
#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;
using TUP = tuple<int, int, int, int>;

const int N = 1e2 + 5;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

int n, m;
char mp[N][N];
int dist[N][N];
int sx, sy, ex, ey;

int BFS() {
  memset(dist, 0x3F, sizeof dist);
  dist[sx][sy] = 0;

  deque<TUP> dq;
  dq.emplace_back(sx, sy, 0, -1);

  while (!dq.empty()) {
    auto [x, y, turn, dir] = dq.front();
    dq.pop_front();

    if (x == ex && y == ey) return turn;

    for (int i = 0; i < 4; i++) {
      int tx = x + dx[i];
      int ty = y + dy[i];
      bool turned = (i != dir && dir != -1);

      if (tx < 1 || ty < 1 || tx > n || ty > m) continue;
      if (mp[tx][ty] == '*') continue;

      if (dist[tx][ty] >= turn + turned) {
        dist[tx][ty] = turn + turned;
        if (!turned)
          dq.emplace_front(tx, ty, turn, i);
        else
          dq.emplace_back(tx, ty, turn + 1, i);
      }
    }
  }

  return -1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> m >> n;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
      char ch;
      cin >> ch;

      mp[i][j] = ch;
      if (ch != 'C') continue;

      if (!sx)
        sx = i, sy = j;
      else
        ex = i, ey = j;
    }

  cout << BFS() << endl;
  fflush(stdout);
  return 0;
}
