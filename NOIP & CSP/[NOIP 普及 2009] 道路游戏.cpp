#include <cstring>
#include <iostream>

using namespace std;

const int N = 1e3 + 10;
const int INF = 0x3f3f3f3f;

int n, m, p, ans = -INF;
int f[N][N][2], coin[N][N], pre[N][N], cost[N];

int cal(int i, int j, int k) {
  return pre[i - 1][j - 1] - pre[i - k - 1][j - k - 1];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  memset(f, -0x3f, sizeof(f));

  cin >> n >> m >> p;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
      cin >> coin[i][j];
      pre[j][i] = pre[j - 1][i - 1] + coin[i][j];
    }

  for (int i = 1; i <= n; i++) {
    cin >> cost[i];
    f[1][i][0] = -cost[i];
  }

  m += 1;

  for (int i = 2; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      for (int k = 1; k <= min(i, p); k++)
        if (j > k)
          f[i][j][1] = max(f[i][j][1], f[i - k][j - k][0] + cal(i, j, k));
        else if (i > j)
          f[i][j][1] = max(f[i][j][1], f[i - k][n + j - k][0] + cal(i - j + 1, n + 1, k - j + 1) + cal(i, j, j - 1));
    }

    for (int j = 1; j <= n; j++)
      for (int k = 1; k <= n; k++) {
        if (k == j) continue;
        f[i][j][0] = max(f[i][j][0], f[i][k][1] - cost[j]);
      }
  }

  for (int i = 1; i <= n; i++)
    ans = max(ans, f[m][i][1]);
  cout << ans << endl;
  return 0;
}
