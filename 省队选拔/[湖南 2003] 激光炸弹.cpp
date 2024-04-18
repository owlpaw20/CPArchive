#include <iostream>

#define endl '\n'

using namespace std;

const int N = 5e3 + 10;

int n, m, p[N][N];
int x, y, v, ans = -1;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> x >> y >> v;
    p[x + 1][y + 1] = v;
  }

  for (int i = 1; i <= 5001; i++)
    for (int j = 1; j <= 5001; j++)
      p[i][j] = p[i - 1][j] + p[i][j - 1] - p[i - 1][j - 1] + p[i][j];

  for (int i = m; i <= 5001; i++)
    for (int j = m; j <= 5001; j++)
      ans = max(ans, p[i][j] - p[i - m][j] - p[i][j - m] + p[i - m][j - m]);

  cout << ans << endl;
  fflush(stdout);
  return 0;
}
