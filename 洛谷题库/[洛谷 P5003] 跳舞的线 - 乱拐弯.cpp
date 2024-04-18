#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1e3 + 10;
const int INF = 0x3F3F3F3F;

int n, m;
bool mp[N][N];
int f[N][N][2], g[N][N][2];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  memset(f, 0xCF, sizeof f);
  memset(g, 0x3F, sizeof g);

  char t;
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      cin >> t, mp[i][j] = (t == '#' ? true : false);

  if (mp[1][1])
    return puts("-1") && 0;

  f[1][1][0] = f[1][1][1] = g[1][1][0] = g[1][1][1] = 0;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      if (!mp[i][j])
        f[i][j][0] = max({f[i][j][0], f[i][j - 1][0], f[i - 1][j][1] + 1}),
        f[i][j][1] = max({f[i][j][1], f[i - 1][j][1], f[i][j - 1][0] + 1}),
        g[i][j][0] = min({g[i][j][0], g[i][j - 1][0], g[i - 1][j][1] + 1}),
        g[i][j][1] = min({g[i][j][1], g[i - 1][j][1], g[i][j - 1][0] + 1});

  if (g[n][m][0] == INF && g[n][m][1] == INF)
    return puts("-1") && 0;

  cout << max(f[n][m - 1][0], f[n - 1][m][1]) << " ";
  cout << min(g[n][m - 1][0], g[n - 1][m][1]) << endl;
  return 0;
}
