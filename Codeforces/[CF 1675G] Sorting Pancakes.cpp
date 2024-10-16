#pragma GCC optimize("O2,unroll-loops")
#include <bits/stdc++.h>

const int MAX_N = 255;
const int INF = 0x3F3F3F3F;

int N, M, a[MAX_N];
int f[MAX_N][MAX_N][MAX_N];
// f[i][j][k] 表示前 i 个盘子共放了 j 个馅饼，第 i 个盘子放了 k 个馅饼的最小操作次数

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;
  for (int i = 1; i <= N; ++i) std::cin >> a[i], a[i] += a[i - 1];

  // 初始化
  memset(f, 0x3F, sizeof f);
  for (int i = 0; i <= M; ++i) f[0][0][i] = 0;

  for (int i = 0; i < N; ++i)
    for (int j = 0; j <= M; ++j)    // 前缀馅饼总数 j 不超过 m
      for (int k = 0; k <= j; ++k)  // 当前盘子里的馅饼数量 k 不超过前缀总量 j
        if (f[i][j][k] ^ INF)
          // 枚举第 i + 1 个盘子里馅饼的数量 l 进行转移
          for (int l = 0, lim = i ? std::min(M - j, k) : M - j; l <= lim; ++l)
            // 只向右侧拿取馅饼，则加入从 i + 2 拿取所产生的操作次数
            f[i + 1][j + l][l] = std::min(f[i + 1][j + l][l], f[i][j][k] + abs(j + l - a[i + 1]));

  std::cout << *std::min_element(f[N][M], f[N][M] + M + 1) << std::flush;
  return 0;
}
