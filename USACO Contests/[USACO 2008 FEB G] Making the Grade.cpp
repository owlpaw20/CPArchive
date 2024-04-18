// 重要引理的证明请见《算法竞赛进阶指南》新版第 294 页
// 结论：一定存在一种最优情况，使得 B 序列中的每一个值都在 A 序列中出现过。

#include <limits>
#include <iostream>
#include <algorithm>

#define endl '\n'

const int MAX_N = 2e3 + 5;

int N;
int a[MAX_N], b[MAX_N];
int f[MAX_N][MAX_N];  // f[i][j] 表示当第 i 条道路的高度为 b[j] 时，修理完前 i 条路所需的花费
int g[MAX_N][MAX_N];  // g[i][j] 表示 f[i][k] where k in [1, j) 的最小值

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;

  for (int i = 1; i <= N; ++i)
    std::cin >> a[i], b[i] = a[i];

  // 如果最优解是单调不降的
  std::sort(b + 1, b + N + 1);

  for (int i = 1; i <= N; ++i) {
    g[i][0] = std::numeric_limits<int>::max();
    for (int j = 1; j <= N; ++j) {
      f[i][j] = g[i - 1][j] + abs(a[i] - b[j]);
      g[i][j] = std::min(g[i][j - 1], f[i][j]);
    }
  }

  int ans_1 = g[N][N];

  // 如果最优解是单调不增的
  for (int i = 0; i <= N; ++i)
    for (int j = 0; j <= N; ++j)
      f[i][j] = g[i][j] = 0;

  std::reverse(b + 1, b + N + 1);

  for (int i = 1; i <= N; ++i) {
    g[i][0] = std::numeric_limits<int>::max();
    for (int j = 1; j <= N; ++j) {
      f[i][j] = g[i - 1][j] + abs(a[i] - b[j]);
      g[i][j] = std::min(g[i][j - 1], f[i][j]);
    }
  }

  int ans_2 = g[N][N];

  // 取单调不降和单调不增两种情况中的较优解
  std::cout << std::min(ans_1, ans_2) << endl;
  return fflush(stdout), 0;
}
