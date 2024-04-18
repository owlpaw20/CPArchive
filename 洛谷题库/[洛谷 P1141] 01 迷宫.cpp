#include <vector>
#include <numeric>
#include <iostream>

#define endl '\n'

using namespace std;

struct DisjointSet {
  vector<int> p;
  vector<int> cnt;
  void init(int n) {
    p.resize(n + 1);
    cnt.assign(n + 1, 1);
    iota(p.begin(), p.end(), 0);
  }
  int find(int x) {
    if (p[x] == x) return x;
    return p[x] = find(p[x]);
  }
  bool merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return false;
    return p[x] = y, cnt[y] += cnt[x], true;
  }
};

const int N = 1e3 + 5;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

int n, m;
bool g[N][N];
DisjointSet DSU;

int H(int x, int y) {
  return (x - 1) * n + y;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;
  DSU.init(n * n);

  char ch;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      cin >> ch, g[i][j] = (ch == '1');

  for (int x = 1; x <= n; x++)
    for (int y = 1; y <= n; y++)
      for (int i = 0; i < 4; i++) {
        int tx = x + dx[i], ty = y + dy[i];
        if (tx < 1 || ty < 1 || tx > n || ty > n) continue;
        if (g[x][y] == g[tx][ty]) continue;
        DSU.merge(H(x, y), H(tx, ty));
      }

  while (m--) {
    int sx, sy;
    cin >> sx >> sy;
    cout << DSU.cnt[DSU.find(H(sx, sy))] << endl;
  }

  fflush(stdout);
  return 0;
}
