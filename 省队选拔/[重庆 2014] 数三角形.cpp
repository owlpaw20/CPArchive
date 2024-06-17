#include <iostream>

using LL = long long;

int N, M;

LL nC3(LL n) { return n * (n - 1) * (n - 2) / 6; }

template <typename intT>
intT gcd(intT a, intT b) { return b ? gcd(b, a % b) : a; }

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;

  LL ans = nC3((N + 1) * (M + 1));       // 在网格内任取三个点的方案数
  LL vertical = nC3(N + 1) * (M + 1);    // 任取三个点共一条竖直线的方案数
  LL horizontal = nC3(M + 1) * (N + 1);  // 任取三个点共一条水平线的方案数

  ans -= vertical + horizontal;

  // 枚举水平方向的坐标差
  for (int i = 1; i <= N; ++i)
    // 枚举数值方向的坐标差
    for (int j = 1; j <= M; ++j)
      // 枚举所有可能的斜线以及斜线上找到第三个格点的方案数
      // 乘以 2 是因为斜率可能正也可能负
      ans -= 2 * (N - i + 1) * (M - j + 1) * (gcd(i, j) - 1);

  std::cout << ans << std::endl;
  return 0;
}
