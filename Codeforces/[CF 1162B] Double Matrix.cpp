#include <iostream>

#define endl '\n'

using namespace std;

const int N = 60;

int n, m;
int a[N][N], b[N][N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) cin >> a[i][j];
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) cin >> b[i][j];

  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      if (a[i][j] > b[i][j])
        swap(a[i][j], b[i][j]);

  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      if ((i < n && (a[i][j] >= a[i + 1][j] || b[i][j] >= b[i + 1][j])) ||
          (j < m && (a[i][j] >= a[i][j + 1] || b[i][j] >= b[i][j + 1]))) {
        puts("Impossible");
        return 0;
      }

  puts("Possible");
  fflush(stdout);
  return 0;
}
