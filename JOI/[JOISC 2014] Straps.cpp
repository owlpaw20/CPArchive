#include <cstring>
#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;
using PII = pair<int, int>;

const int N = 2e3 + 10;
const int M = 4e3 + 10;  // 开到 4000 是为了转移时避免 (j - 1 + hk) 数组越界
const int INF = 0xCFCFCFCF;

int n;
PII d[N];
int f[N][M];
// f[i][j] 表示挂好了前 i 个物品，剩余 j 个挂钩未使用时的最大喜悦值

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  memset(f, 0xCF, sizeof f);

  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> d[i].first >> d[i].second;

  sort(d + 1, d + n + 1, greater<PII>());

  f[0][1] = 0;  // 手机上最开始本身有一个挂钩，此时作为初始状态

  for (int i = 1; i <= n; i++)
    for (int j = 0; j <= n << 1; j++) {
      f[i][j] = max(f[i][j], f[i - 1][j]);  // 如果当前没有能挂的钩子就直接继承此前的状态

      if (j) {  // 如果有能挂的钩子
        auto [hk, val] = d[i];

        // 就更新当前状态的最大喜悦值为 (前 i - 1 个物品的最大喜悦值) 与
        // (前 i - 1 个物品的最大喜悦值 + 当前物品 i 的喜悦值) 中的较大值
        f[i][j - 1 + hk] = max(f[i - 1][j - 1 + hk], f[i - 1][j] + val);
      }
    }

  int ans = INF;
  for (int i = 0; i <= n << 1; i++)
    ans = max(ans, f[n][i]);

  cout << ans << endl;
  fflush(stdout);
  return 0;
}
