#include <iostream>
#include <algorithm>

#define endl '\n'

using PII = std::pair<int, int>;

const int PF = 8;
const int MAX_N = 5e2 + 5;
const int primes[] = {2, 3, 5, 7, 11, 13, 17, 19};
const int MAX_ST = 1 << PF;

int N;
int MOD;
PII max_pf[MAX_N];

int f[MAX_ST][MAX_ST];
// f[i][j][k] = 前 i 个数中，小 G 所选质因数的集合为 j，小 W 所选质因数的集合为 k 的方案数

// 在 500 以内，每个数最多拥有一个大于 sqrt(500) 的质因数，
// 则对这些较大的质因数进行单独考虑。将其排序，以将不同数字中相同的大质因数合在一块考虑。
int g[MAX_ST][MAX_ST];  // 对于大质因数相同的某连续段，该大质因数只被小 G 选或不被选的方案数
int h[MAX_ST][MAX_ST];  // 对于大质因数相同的某连续段，该大质因数只被小 W 选或不被选的方案数

namespace Modulo {
  inline int mod(const int x) { return (x < MOD) ? ((x < 0) ? (x + MOD) : x) : (x - x / MOD * MOD); }
  inline int add(const int x, const int y) { return mod(x + y); }
}  // namespace Modulo
using namespace Modulo;

// 预处理每个整数的大质因子，并标记当前整数小质因子的存在状态
void prep() {
  for (int i = 2; i <= N; ++i) {
    max_pf[i].first = i;
    for (int j = 0; j < PF; ++j)
      while (max_pf[i].first % primes[j] == 0)
        max_pf[i].first /= primes[j], max_pf[i].second |= (1 << j);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> MOD;

  prep();

  std::sort(max_pf + 2, max_pf + N + 1);  // 按照大质因子大小进行聚集

  g[0][0] = 1;

  for (int i = 2; i <= N; ++i) {
    // 如果当前整数没有大质因数或者遍历到了下一个大质因数
    if (max_pf[i].first == 1 || max_pf[i].first != max_pf[i - 1].first)
      for (int j = MAX_ST - 1, c; ~j; --j) {
        // 遍历小 G 对前 8 个质因数的选择情况
        c = (MAX_ST - 1) ^ j;

        // 在补集中遍历小 W 对前 8 个质因数的选择情况
        // 需要减去一个 f[j][k] 的原因是，所有数都不选的情况在 g 和 h 中各被计算了一次，总共统计了两次
        for (int k = c; k; k = (k - 1) & c)
          g[j][k] = h[j][k] = f[j][k] = add(add(g[j][k], h[j][k]), -f[j][k]);
        g[j][0] = h[j][0] = f[j][0] = add(add(g[j][0], h[j][0]), -f[j][0]);
      }

    // 考虑存在大质因数的情况
    for (int j = MAX_ST - 1, t = max_pf[i].second, c; ~j; --j) {
      // 遍历小 G 对前 8 个质因数的选择情况
      c = (MAX_ST - 1) ^ j;

      // 在补集中遍历小 W 对前 8 个质因数的选择情况
      for (int k = c; k; k = (k - 1) & c) {
        // 如果当前整数的其他质因子不与小 W 重合，则统计到小 G 身上
        if (!(k & t)) g[j | t][k] = add(g[j | t][k], g[j][k]);
        // 如果当前整数的其他质因子不与小 G 重合，则统计到小 W 身上
        if (!(j & t)) h[j][k | t] = add(h[j][k | t], h[j][k]);
      }
      // 如果小 W 不选，则将该大质因数直接统计到 G 身上
      g[j | t][0] = add(g[j | t][0], g[j][0]);
      // 如果当前整数的其他质因子不与小 G 重合，则统计到小 W 身上
      if (!(j & t)) h[j][t] = add(h[j][t], h[j][0]);
    }
  }

  int ans = 0;
  for (int i = MAX_ST - 1, c; ~i; --i) {
    c = (MAX_ST - 1) ^ i;
    for (int j = c; j; j = (j - 1) & c)
      ans = add(ans, add(add(g[i][j], h[i][j]), -f[i][j]));
    ans = add(ans, add(add(g[i][0], h[i][0]), -f[i][0]));
  }

  std::cout << ans << endl;
  return fflush(stdout), 0;
}
