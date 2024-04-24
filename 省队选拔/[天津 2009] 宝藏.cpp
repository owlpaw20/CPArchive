#include <tuple>
#include <vector>
#include <iostream>

#define endl '\n'

using TUP = std::tuple<int, int, int, int>;

const int MAX_NM = 30;
const int MAX_K = 10;
const int MAX_STATES = 1 << MAX_K;
const int MAX_Q = MAX_NM * MAX_NM * MAX_STATES + 5;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};

int n, m, K;
std::vector<TUP> machine;
char maze[MAX_NM + 5][MAX_NM + 5];

int sx, sy;
TUP q[MAX_Q];
bool vis[MAX_NM + 5][MAX_NM + 5][MAX_STATES];

int BFS() {
  int qh = 0, qr = 0;

  vis[sx][sy][0] = true;
  q[0] = TUP(sx, sy, 0, 0);

  while (qh <= qr) {
    auto [x, y, state, step] = q[qh++];

    if (maze[x][y] == 'T') return step;

    for (int i = 0; i < 4; ++i) {
      int tx = x + dx[i], ty = y + dy[i];
      if (tx < 1 || ty < 1 || tx > n || ty > m) continue;

      bool is_blocked = (maze[tx][ty] == '#');
      int t_state = state;

      for (int j = 0; j < K; ++j) {
        auto [x1, y1, x2, y2] = machine[j];
        if (x1 == tx && y1 == ty) t_state ^= (1 << j);
        if (x2 == tx && y2 == ty && ((state >> j) & 1)) is_blocked ^= 1;
      }

      if (is_blocked || vis[tx][ty][t_state]) continue;

      vis[tx][ty][t_state] = true;
      q[++qr] = TUP(tx, ty, t_state, step + 1);
    }
  }

  return -1;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> m;

  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) {
      std::cin >> maze[i][j];
      if (maze[i][j] == 'S') sx = i, sy = j;
    }

  std::cin >> K;
  machine.resize(K);
  for (auto& [x1, y1, x2, y2] : machine) std::cin >> x1 >> y1 >> x2 >> y2;

  std::cout << BFS() << endl;
  return fflush(stdout), 0;
}
