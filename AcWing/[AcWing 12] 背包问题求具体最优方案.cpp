#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e3 + 10;

int n, m;
int f[N][N];
int c[N], v[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    cin >> c[i] >> v[i];

  for (int i = n; i > 0; i--)
    for (int j = 0; j <= m; j++) {
      f[i][j] = f[i + 1][j];
      if (j >= c[i])
        f[i][j] = max(f[i][j], f[i + 1][j - c[i]] + v[i]);
    }

  for (int i = 1, j = m; i <= n; i++)
    if (j >= c[i])
      if (f[i][j] == f[i + 1][j - c[i]] + v[i])
        cout << i << ' ', j -= c[i];

  fflush(stdout);
  return 0;
}
