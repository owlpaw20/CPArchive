#include <queue>
#include <cstring>
#include <iostream>
#define endl '\n'

using namespace std;
using PII = pair<int, int>;

const int N = 1e3 + 10;
const int INF = 0x3F3F3F3F;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

int n, m;
char g[N][N];
int dist[N][N];

void BFS() {
  queue<PII> q;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      if (g[i][j] == '1')
        q.emplace(i, j), dist[i][j] = 0;

  while (!q.empty()) {
    auto [x, y] = q.front();
    for (int i = 0; i < 4; i++) {
      int tx = x + dx[i], ty = y + dy[i];
      if (tx < 1 || ty < 1 || tx > n || ty > m) continue;
      if (dist[tx][ty] == INF) {
        dist[tx][ty] = dist[x][y] + 1;
        q.emplace(tx, ty);
      }
    }
    q.pop();
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  memset(dist, 0x3F, sizeof dist);

  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      cin >> g[i][j];

  BFS();

  for (int i = 1; i <= n; i++, cout.put('\n'))
    for (int j = 1; j <= m; j++)
      cout << dist[i][j] << ' ';
  fflush(stdout);
  return 0;
}
