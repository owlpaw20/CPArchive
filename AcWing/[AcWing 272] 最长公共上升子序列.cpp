#include <iostream>
using namespace std;

const int N = 3e3 + 10;

int n, a[N], b[N];
int f[N][N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= n; i++) cin >> b[i];

  for (int i = 1; i <= n; i++) {
    int maxval = 1;
    for (int j = 1; j <= n; j++) {
      f[i][j] = f[i - 1][j];
      if (a[i] == b[j])
        f[i][j] = max(f[i][j], maxval);
      if (a[i] > b[j])
        maxval = max(maxval, f[i - 1][j] + 1);
    }
  }

  int ans = 0;
  for (int i = 1; i <= n; i++)
    ans = max(ans, f[n][i]);

  cout << ans << endl;
  return 0;
}
