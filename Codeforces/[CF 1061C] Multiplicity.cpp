#include <bits/stdc++.h>

constexpr int MAX_N = 1e5 + 5;
constexpr int MAX_M = 1e6 + 5;
constexpr int MAX_F = 5e2 + 5;
constexpr int MOD = 1e9 + 7;

int N, a[MAX_N];
int f[MAX_M], fac[MAX_F];

// f[i][j] 表示在 a 序列前 i 个元素中选出 b 序列前 j 个元素的方案数
// 转移时，若 a[i] 不为 j 的倍数，那么不能选，转移方程为 f[i][j] = f[i - 1][j]
// 若 a[i] 为 j 的倍数，那么可选可不选，转移方程为 f[i][j] = f[i - 1][j] + f[i - 1][j - 1]
// 我们可以将第一维通过滚动数组优化掉，这样一来我们只需要考虑 a[i] 为 j 倍数的所有转移

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  for (int i = 1; i <= N; ++i) std::cin >> a[i];

  f[0] = 1;  // 初始化状态

  for (int i = 1, cnt = 0; i <= N; ++i, cnt = 0) {
    for (int j = 1, lim = sqrt(a[i]); j <= lim; ++j)  // 预处理出 a[i] 的所有因数
      if (a[i] % j == 0) {
        fac[++cnt] = j;
        if (j * j != a[i]) fac[++cnt] = a[i] / j;
      }

    // 对于 a[i] 的所有因数 p，b 序列位置为 p 的元素可为也可不为 a[i]
    // 由此来进行转移，需要注意的是要从较大的因数开始转移，防止后效性的产生
    std::sort(fac + 1, fac + cnt + 1, std::greater<int>());
    for (int i = 1; i <= cnt; ++i) f[fac[i]] = (f[fac[i]] + f[fac[i] - 1]) % MOD;
  }

  std::cout << std::accumulate(f + 1, f + N + 1, 0LL) % MOD << std::flush;
  return 0;
}
