// 参考题解：https://www.luogu.com.cn/article/pjxavc1w

#include <cstdint>
#include <numeric>
#include <iostream>
#include <initializer_list>

#define endl '\n'

using u32 = uint32_t;
using u64 = uint64_t;

const int MAX_N = 5e2 + 5;
const int MOD = 1e9 + 7;

int N, K;
char c[MAX_N];
u32 f[MAX_N][MAX_N][5];

/*
    f[i][j][p] 表示区间 [i, j] 的状态为 p 时的合法方案数

    p = 0 表示区间内字符全为 *
    p = 1 表示左右端点是一组单区间匹配的括号
    p = 2 表示区间左端点为 (，右端点为 *
    p = 3 表示左右端点是一组匹配的括号
    p = 4 表示区间左端点为 *，右端点为 )
*/

namespace MODULO {
  u32 mul(const u32 x, const u32 y) { return ((u64)x * y) % MOD; }
  u32 add(const u32 x, const u32 y) { return ((u32)x + y) % MOD; }
  u32 add(const std::initializer_list<u32> x) { return std::accumulate(x.begin(), x.end(), 0ULL) % MOD; }
}  // namespace MODULO
using namespace MODULO;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  (std::cin >> N >> K).get();
  for (int i = 1; i <= N; ++i) c[i] = std::cin.get();

  for (int i = 1; i <= N; ++i) f[i][i - 1][0] = 1;

  for (int len = 1; len <= N; ++len)
    for (int l = 1, r = len; r <= N; ++l, ++r) {
      if (len <= K && f[l][r - 1][0] && (c[r] == '*' || c[r] == '?'))
        f[l][r][0] = 1;

      if (len >= 2) {
        if ((c[l] == '(' || c[l] == '?') && (c[r] == ')' || c[r] == '?'))
          f[l][r][1] = add({f[l + 1][r - 1][0], f[l + 1][r - 1][2], f[l + 1][r - 1][3], f[l + 1][r - 1][4]});

        for (int p = l; p < r; ++p) {
          f[l][r][2] = add(f[l][r][2], mul(f[l][p][3], f[p + 1][r][0]));
          f[l][r][3] = add(f[l][r][3], mul(add(f[l][p][2], f[l][p][3]), f[p + 1][r][1]));
          f[l][r][4] = add(f[l][r][4], mul(f[l][p][0], f[p + 1][r][3]));
        }
      }

      f[l][r][3] = add(f[l][r][3], f[l][r][1]);
    }

  std::cout << f[1][N][3] << endl;
  return fflush(stdout), 0;
}
