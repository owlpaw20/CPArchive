#include <bits/stdc++.h>

using i64 = long long;

const int MAX_N = 1e3 + 5;
const int MAX_M = 1e4 + 5;

int N, W, B, X;
int cnt[MAX_N], cost[MAX_N];
i64 f[MAX_N][MAX_M], pcnt[MAX_N];  // f[i][j] 表示走到第 i 棵树下召唤了 j 只鸟时的最大魔力

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> W >> B >> X;
  for (int i = 1; i <= N; ++i) std::cin >> cnt[i], pcnt[i] = pcnt[i - 1] + cnt[i];
  for (int i = 1; i <= N; ++i) std::cin >> cost[i];

  memset(f, -1, sizeof f);
  f[0][0] = W;

  for (int i = 1; i <= N; ++i)
    for (int j = 0; j <= pcnt[i]; ++j)             // 枚举已经召唤的总鸟数
      for (int k = 0; k <= j && k <= cnt[i]; ++k)  // 枚举在当前树下召唤的鸟数
        if (f[i - 1][j - k] >= (i64)k * cost[i])   // 确保状态存在（-1 恒小于 k * cost[i] 故省略）且能够转移
          f[i][j] = std::max(f[i][j], std::min(W + (i64)B * j, f[i - 1][j - k] - (i64)k * cost[i] + X));

  for (int i = 1; i <= pcnt[N] + 1; ++i)
    if (f[N][i] == -1)
      return std::cout << i - 1 << std::flush, 0;

  return 0;
}
