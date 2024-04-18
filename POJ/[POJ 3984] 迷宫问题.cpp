#include <queue>
#include <cstring>
#include <iostream>

using namespace std;

using PII = pair<int, int>;

const int N = 1e3 + 5;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

int n;
int map[N][N];
PII lst[N][N];

void BFS(int sx, int sy) {
  queue<PII> q;
  q.emplace(sx, sy);
  memset(lst, -1, sizeof lst);
  lst[sx][sy] = PII(0, 0);

  while (!q.empty()) {
    auto [x, y] = q.front();
    for (int i = 0; i < 4; i++) {
      int tx = x + dx[i], ty = y + dy[i];
      if (tx < 0 || tx >= n || ty < 0 || ty >= n) continue;
      if (map[tx][ty] || lst[tx][ty].first != -1) continue;
      q.emplace(tx, ty);
      lst[tx][ty] = q.front();
    }
    q.pop();
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      cin >> map[i][j];

  BFS(n - 1, n - 1);

  PII pos(0, 0);

  while (true) {
    auto [x, y] = pos;
    cout << x << ' ' << y << '\n';
    if (x == n - 1 && y == n - 1) break;
    pos = lst[x][y];
  }

  fflush(stdout);
  return 0;
}
