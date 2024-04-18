#include <iostream>

#define endl '\n'

using namespace std;

const int N = 10;

int n;
int vis[N][N][N][N][N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;

  for (int i = 1; i <= n; i++) {
    int a, b, c, d, e;
    cin >> a >> b >> c >> d >> e;
    for (int j = 1; j <= 9; j++) {
      vis[(a + j) % 10][b][c][d][e]++;
      vis[a][(b + j) % 10][c][d][e]++;
      vis[a][b][(c + j) % 10][d][e]++;
      vis[a][b][c][(d + j) % 10][e]++;
      vis[a][b][c][d][(e + j) % 10]++;
      vis[(a + j) % 10][(b + j) % 10][c][d][e]++;
      vis[a][(b + j) % 10][(c + j) % 10][d][e]++;
      vis[a][b][(c + j) % 10][(d + j) % 10][e]++;
      vis[a][b][c][(d + j) % 10][(e + j) % 10]++;
    }
  }

  int ans = 0;
  for (int i = 0; i <= 9; i++)
    for (int j = 0; j <= 9; j++)
      for (int k = 0; k <= 9; k++)
        for (int l = 0; l <= 9; l++)
          for (int m = 0; m <= 9; m++)
            if (vis[i][j][k][l][m] == n)
              ans++;

  fflush(stdout);
  cout << ans << endl;
  return 0;
}
