// 加强版提交处为 [AcWing 99](激光炸弹)

#pragma GCC optimize("O2,unroll-loops")

#include <iostream>

#define endl '\n'

using namespace std;

const int N = 5e3 + 10;

int n, r, p[N][N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> r;
  int x, y, w, mxx = 0, mxy = 0;
  for (int i = 1; i <= n; i++) {
    cin >> x >> y >> w;
    p[x + 1][y + 1] += w;
    mxx = max(x + 1, mxx);
    mxy = max(y + 1, mxy);
  }

  for (int i = 1; i <= 5001; i++)
    for (int j = 1; j <= 5001; j++)
      p[i][j] = p[i - 1][j] + p[i][j - 1] - p[i - 1][j - 1] + p[i][j];

  if (r >= mxx && r >= mxy)
    return (cout << p[5001][5001] << endl) && 0;

  int ans = 0;
  for (int i = r; i <= 5001; i++)
    for (int j = r; j <= 5001; j++)
      ans = max(ans, p[i][j] - p[i - r][j] - p[i][j - r] + p[i - r][j - r]);

  cout << ans << endl;
  fflush(stdout);
  return 0;
}
