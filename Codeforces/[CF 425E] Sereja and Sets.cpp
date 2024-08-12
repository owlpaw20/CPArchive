#include <bits/stdc++.h>

using i64 = long long;

const int MAX_N = 5e2 + 5;
const int MOD = 1e9 + 7;

int N, K;
int f[MAX_N][MAX_N];
int p2[MAX_N * MAX_N];

/*
  考虑类似于线段覆盖的基于贪心的 DP 做法。

  设 f[i][j] 表示以 i 作为当前已选线段的最右端点，j 为当前已选的线段数量，
  则可以枚举下一个选择的最小右端点 k (k > i) 进行转移。

  由于我们钦定 k 为所选的最小右端点，
    所以不能出现右端点小于 k 的线段。

  先考虑线段在 i 到 k 之间的情况：
    由于已经确定了右端点为 k，
    且下一条线段的左端点不能与 i 重合，
    所以左端点共有 k - i 种合法位置。
    又由于在这段区间内可以存在任意数量的线段（只要它的右端点在 k 处），
    所以这段区间内的所有线段共有 2 ^ (k - i) 种可能。
    由于我们钦定了必须要存在至少一条线段的右端点为 k，
    所以实际上还需要减掉这些左端点都不选择的这一种情况，
    最终情况数为 2 ^ (k - i) - 1。

  接着考虑对跨越了 k 的线段进行计数：
    这类线段要求左端点在 (i, k] 范围内，根据前一种情况的分析可知有 (k - i) 种情况；
    右端点则可以在 (k, N] 范围内，有 (N - k) 种情况。
    可以不存在任何跨越 k 的线段，
    所以最终情况数为 2 ^ ((N - k) * (k - i))

  综上，根据乘法原理，转移就是把这些情况全部乘起来。
*/

void prep(int n) {
  p2[0] = 1;
  for (int i = 1; i <= n; ++i) p2[i] = (p2[i - 1] << 1) % MOD;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> K, prep(N * N);

  f[0][0] = 1;

  for (int i = 0; i <= N; ++i)
    for (int j = 0; j <= K; ++j)
      for (int k = i + 1; k <= N; ++k)
        f[k][j + 1] = (f[k][j + 1] + (i64)f[i][j] * p2[(N - k) * (k - i)] % MOD * (p2[k - i] - 1) % MOD) % MOD;

  int ans = 0;
  for (int i = 0; i <= N; ++i) ans = (ans + f[i][K]) % MOD;

  std::cout << ans << std::flush;
  return 0;
}
