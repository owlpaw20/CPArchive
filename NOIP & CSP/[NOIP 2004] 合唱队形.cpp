#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e2 + 10;

int n, h[N];
int f[N][2];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> h[i];
    f[i][0] = f[i][1] = 1;
  }

  // 求 h[1] ~ h[i] 的最长上升子序列长度
  for (int i = 1; i <= n; i++)
    for (int j = 1; j < i; j++)
      if (h[i] > h[j])
        f[i][0] = max(f[i][0], f[j][0] + 1);

  // 求 h[i] ~ h[n] 的最长下降子序列长度
  for (int i = n; i > 0; i--)
    for (int j = n; j > i; j--)
      if (h[i] > h[j])
        f[i][1] = max(f[i][1], f[j][1] + 1);

  // 统计以每个 h[i] 为最大身高时最多能保留多少个元素
  int ans = 0;
  for (int i = 1; i <= n; i++)
    ans = max(ans, f[i][0] + f[i][1] - 1);

  cout << n - ans << endl;
  fflush(stdout);
  return 0;
}
