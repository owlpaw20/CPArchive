#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e3 + 10;
const int M = 2e2 + 10;
const int MOD = 1e9 + 7;

int n, m, K;
int f[M][M];
int sum[M][M];
char a[N], b[M];

/*  f[i][j][k] = a[1 ~ i] 中选取 k 段，可以匹配 b[1 ~ j] 的方案数
    f[i][j][k] = f[i - 1][j][k]               不选 a[i] 的方案数
              + sum(f[i - t][j - t][k - 1])  所有选 a[i-t+1 ~ i] 这一段的方案数之和
    在转移过程中对 sum 进行预处理节省空间，并使用滚动数组优化空间
    sum[i][j][k] = sum[i - 1][j - 1][k] + f[i - 1][j - 1][k - 1] (a[i] == b[j])
                = 0                                             (a[i] != b[j]) */

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m >> K;
  cin >> (a + 1) >> (b + 1);

  f[0][0] = 1;
  for (int i = 1; i <= n; i++)
    for (int j = m; j > 0; j--)
      for (int k = K; k > 0; k--) {
        if (a[i] != b[j])
          sum[j][k] = 0;
        else
          sum[j][k] = (sum[j - 1][k] + f[j - 1][k - 1]) % MOD;
        f[j][k] = (f[j][k] + sum[j][k]) % MOD;
      }

  cout << f[m][K] << endl;
  fflush(stdout);
  return 0;
}
