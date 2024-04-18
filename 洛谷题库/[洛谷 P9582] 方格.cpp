#include <iostream>
using namespace std;
using i64 = long long;

const int N = 2e3 + 10;
const int dx[] = {0, 1, -1, 0};
const int dy[] = {1, 0, 0, -1};

int n, m;
int mp[N][N], flag[10];

int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      cin >> mp[i][j], flag[mp[i][j]]++;
  i64 ans = 0;
  for (int i = 1; i <= 9; i++)
    ans += 1ll * flag[i] * (flag[i] - 1);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      for (int k = 0; k < 4; k++) {
        int tx = i + dx[k], ty = j + dy[k];
        if (mp[tx][ty] == mp[i][j]) ans--;
      }
  cout << ans << endl;
  return 0;
}
