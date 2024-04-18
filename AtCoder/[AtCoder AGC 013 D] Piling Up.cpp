#include <cstdint>
#include <cstring>
#include <iostream>

#define endl '\n'

using u32 = uint32_t;

constexpr int MAX_N = 3e3 + 5;
constexpr int MOD = 1e9 + 7;

int N, M;
u32 f[MAX_N][2], p[MAX_N][2];
// f[i][j][k = 0/1] 表示拿第 i 次之后剩下的白球数量为 j 的情况数，k 表示是否出现过白球 = 0 的情况
// p 为滚动数组，f[i] 这一维被滚动掉了

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;

  // 对于初始存在若干白球的情况，初始不为 k = 1 的特殊情况，方案数为 1
  for (int i = 1; i <= N; ++i) p[i][0] = 1;

  // 对于初始没有白球的情况，初始即为 k = 1 的特殊情况，方案数为 1
  p[0][1] = 1;

  for (int i = 1; i <= M; ++i) {    // 枚举拿球次数
    for (int j = 1; j <= N; ++j) {  // 枚举剩下白球的数量
      // 转移本次操作使白球数量增加的情况
      // 如果白球数量大于 1，则这一次操作一定不是特殊操作，正常转移
      // 如果白球数量恰好为 1，则这一次操作可能是特殊操作，额外转移
      if (j > 1)
        (f[j][0] += p[j][0] + p[j - 1][0]) %= MOD;
      else
        (f[j][1] += p[j][0]) %= MOD;

      (f[j][1] += p[j][1] + p[j - 1][1]) %= MOD;  // 曾经的特殊操作的转移

      // 转移本次操作使白球数量减少的情况
      if (j < N) {
        (f[j][0] += p[j][0] + p[j + 1][0]) %= MOD;
        (f[j][1] += p[j][1] + p[j + 1][1]) %= MOD;
      }
    }

    // 转移循环没有顾及到的特殊情况
    (f[0][1] += p[0][1] + p[1][1] + p[1][0]) %= MOD;

    // 滚动数组
    memcpy(p, f, sizeof f);
    memset(f, 0, sizeof f);
  }

  u32 ans = 0;
  for (int i = 0; i <= N; ++i) (ans += p[i][1]) %= MOD;

  std::cout << ans << endl;
  return fflush(stdout), 0;
}
