#include <iostream>

using namespace std;

const int N = 55;

int m, n, p[N][N], f[N][N][N][N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> m >> n;
  for (int i = 1; i <= m; i++)
    for (int j = 1; j <= n; j++)
      cin >> p[i][j];

  for (int i = 1; i <= m; i++)
    for (int j = 1; j <= n; j++)
      for (int k = 1; k <= m; k++)
        for (int w = 1; w <= n; w++) {
          f[i][j][k][w] = max(
                            max(f[i - 1][j][k - 1][w], f[i - 1][j][k][w - 1]),
                            max(f[i][j - 1][k - 1][w], f[i][j - 1][k][w - 1])) +
                          p[i][j];
          if (i != k && j != w) f[i][j][k][w] += p[k][w];
        }

  cout << f[m][n][m][n] << endl;
  return 0;
}
