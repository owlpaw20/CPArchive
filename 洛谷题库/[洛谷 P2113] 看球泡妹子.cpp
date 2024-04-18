#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e2 + 10;
const int M = 2e3 + 10;

int n, m, k, c;
int a[N], b[N], p[N], q[N];
int f[N][M], maxs;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m >> k >> c;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= n; i++) cin >> b[i];
  for (int i = 1; i <= m; i++) {
    cin >> p[i] >> q[i];
    maxs += b[p[i]] + b[q[i]];
  }

  // f[i][j] 表示看 i 场球赛且小红精彩程度为 j 时小明精彩程度的最大值
  memset(f, 128, sizeof f);
  f[0][0] = 0;
  for (int i = 1; i <= m; i++)
    for (int j = i; j >= 1; j--)
      for (int w = maxs; w >= b[p[i]] + b[q[i]]; w--)
        f[j][w] = max(f[j][w], f[j - 1][w - b[p[i]] - b[q[i]]] + a[p[i]] * a[q[i]]);

  int ans = -1;
  for (int i = c; i <= maxs; i++)
    ans = max(ans, f[k][i]);
  cout << ans << endl;

  fflush(stdout);
  return 0;
}
