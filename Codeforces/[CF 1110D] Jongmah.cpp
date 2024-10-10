#include <bits/stdc++.h>

const int MAX_N = 1e6 + 5;

int N, M, cnt[MAX_N];
int f[MAX_N][3][3];

// f[x][y][z] 表示考虑前 x 种麻将中
// 已经存在 y 个 [x - 1, x, x + 1] 的三元组和 z 个 [x, x + 1, x + 2] 三元组的最大答案
// 由于对于每一个 x，每存在三个 [x, x + 1, x + 2] 就可以转化为三个形如 [x, x, x] 的三元组
// 所以上述的两种三元组都最多只能存在 2 个，由此对状态数进行减小

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;
  for (int i = 1, x; i <= N; ++i) std::cin >> x, ++cnt[x];

  /*
   *  根据状态定义，我们的状态转移需要从 i - 1 时两种三元组分别有 j 和 k 个的状态
   *  转移到 i 时分别有 k 和 l 个的状态。
   *
   *  在此转移过程中，新增的贡献在于：
   *  1. 排除在 i - 1 时已经用过的 j + k 个 i 以及枚举的新状态中所占用的 l 个 i，
   *     剩下的 i 全部用来组成 [i, i, i] 三元组的个数；
   *  2. 以及新状态中所考虑的三元组的个数 l
   */

  for (int i = 1; i <= M; ++i)
    for (int j = 0; j < 3 && j <= cnt[i]; ++j)
      for (int k = 0; k < 3 && j + k <= cnt[i]; ++k)
        for (int l = 0; l < 3 && j + k + l <= cnt[i]; ++l)
          f[i][k][l] = std::max(f[i][k][l], f[i - 1][j][k] + (cnt[i] - j - k - l) / 3 + l);

  std::cout << f[M][0][0] << std::flush;
  return 0;
}
