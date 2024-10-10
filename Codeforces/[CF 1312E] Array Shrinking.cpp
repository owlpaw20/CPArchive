#include <bits/stdc++.h>

const int MAX_N = 5e2 + 5;

int N, a[MAX_N];
int f[MAX_N][MAX_N], g[MAX_N];

// f[l][r] 为原序列区间 [l, r] 能合成哪一个数（若不能合成则为 0）
// g[i] 表示前 i 个数合成之后的最短长度

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  for (int i = 1; i <= N; ++i) std::cin >> a[i], f[i][i] = a[i];

  for (int len = 2; len <= N; ++len)
    for (int l = 1, r = len; r <= N; ++l, ++r)
      for (int mid = l; mid < r; ++mid)               // 枚举区间的断点
        if (f[l][mid] && f[l][mid] == f[mid + 1][r])  // 如果断点左右侧都能合成数且相同
          f[l][r] = f[l][mid] + 1;                    // 那么这两侧就能合并成一个更大的数

  memset(g + 1, 0x3F, sizeof(int) * N);

  for (int i = 1; i <= N; ++i)
    for (int j = 1; j <= i; ++j)                         // 枚举转移点
      f[j][i] && (g[i] = std::min(g[i], g[j - 1] + 1));  // 如果转移点到当前位置能合并则转移

  std::cout << g[N] << std::flush;
  return 0;
}
