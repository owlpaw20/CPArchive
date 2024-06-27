#include <cstring>
#include <iostream>

using LL = long long;

const int MAX_N = 1e2 + 5;
const int MAX_M = 2e3 + 5;
const int MOD = 998244353;

int N, M, a[MAX_N][MAX_M];

LL sum[MAX_N];
int ex_sum[MAX_N][MAX_M];

LL f[MAX_N][MAX_N << 1];  // 不合法状态数（由于实际状态转移涉及负数下标，所以整体右移 N 位）
LL g[MAX_N][MAX_N];       // 合法状态数

// f[i][j] 表示第 i 种烹饪方式下选择的所有菜品中，使用钦定的主要食材 c 的数量减去使用其他主要食材的数量
// g[i][j] 表示前 i 种烹饪方式下，选择了 j 道菜的方案数

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;

  for (int i = 1; i <= N; ++i)
    for (int j = 1; j <= M; ++j)
      std::cin >> a[i][j], sum[i] += a[i][j];

  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= M; ++j)
      ex_sum[i][j] = (sum[i] - a[i][j]) % MOD;
    sum[i] %= MOD;
  }

  // 统计不合法方案数
  LL invalid = 0;

  for (int c = 1; c <= M; ++c) {
    memset(f, 0, sizeof(LL) * ((N + 1) * (N + 1) * 2));
    f[0][N] = 1;  // 初始化方案数

    for (int i = 1; i <= N; ++i)
      for (int j = N - i; j <= N + i; ++j) {
        f[i][j] = f[i - 1][j];                                                    // 烹饪方式 i 下不选任何菜品
        j && (f[i][j] = (f[i][j] + f[i - 1][j - 1] * a[i][c] % MOD) % MOD);       // 烹饪方式 i 下选择主要食材 c
        j && (f[i][j] = (f[i][j] + f[i - 1][j + 1] * ex_sum[i][c] % MOD) % MOD);  // 烹饪方式 i 下选择其他主要食材
      }

    // 统计所有满足当前食材所选数量大于其他食材所选数量总和的情况数，这是不合法情况
    for (int i = 1; i <= N; ++i) invalid = (invalid + f[N][N + i]) % MOD;
  }

  // 统计总方案数
  g[0][0] = 1;
  for (int i = 1; i <= N; ++i)
    for (int j = 0; j <= N; ++j)
      g[i][j] = j ? (g[i - 1][j] + g[i - 1][j - 1] * sum[i] % MOD) % MOD : g[i - 1][j];

  LL total = 0;
  for (int i = 1; i <= N; ++i) total = (total + g[N][i]) % MOD;

  std::cout << ((total - invalid) % MOD + MOD) % MOD << std::endl;
  return 0;
}
