#include <bit>
#include <iostream>
#include <limits>

const int MAX_N = 5005;

using i64 = long long;
using u64 = unsigned long long;

int N, expn[MAX_N];
i64 oddf[MAX_N];
int f[MAX_N];

/**********
  考虑 (x, y) 合法的条件。
  设 t 为连续整数的起始项，而 y 为连续整数的项数，故末项为 t + y - 1。
  由等差数列求和公式，x = (t + t + y - 1) * y / 2 = (y - 1) * y / 2 + t * y
  等式两边同时除以 y 得到 x / y = (y - 1) / 2 + t
  整理得 x / y - (y - 1) / 2 = t
  等式两边同时乘以 2 得到 2x / y - y = 2t + 1
  由于 t 为任意整数，得 2x / y - y 为奇数

  我们记任意整数 t = 2^expn(t) * oddf(t)，
  其中 expn(t) 表示属于 t 约数的最大 2 的幂，
  oddf(t) 表示 t / (2^expn(t)) 所得的奇数。

  因此上式可以写为 2^expn(x) * oddf(x) / (2^expn(y) * oddf(y)) - y
  整理得 2^(expn(x) - expn(y) + 1) * oddf(x) / oddf(y) - y
  若使该式子为奇数，我们不难发现，oddf(y) 必须整除 oddf(x)，此外：

    - 若 y 为奇数，则 expn(y) = 0，
      这意味着 2^(expn(x) - expn(y) + 1) * oddf(x) / oddf(y) 必须为偶数
      而后面一半显然为奇数，前面一半若要为偶数，则 expn(x) + 1 >= 1，因此 expn(x) >= 0
      这显然恒成立。

    - 若 y 为偶数，则 2^(expn(x) - expn(y) + 1) * oddf(x) / oddf(y) 必须为奇数
      那么 2^(expn(x) - expn(y) + 1) 必须为奇数，因此 expn(x) - expn(y) + 1 = 0
      也就是说 expn(y) = expn(x) + 1

  现在考虑如果要让序列 a[i...j] 都满足条件有什么限制。
  我们假设 a[i] 和 a[j] 都不修改。
  首先，相邻两项中，后一项必须整除前一项，这表明对于整个序列来说 a[j] 必须整除 a[i]。
  其次，根据我们上面的推导，后一项的 expn 必须为 0 或者是前一项 expn + 1，
  因此要么 a[j] - a[i] = j - i，要么 a[j] <= (j - 1) - (i + 1) + 1 = j - i - 1
  前者表示 expn(j) 是从 expn(i) 逐步 +1 得到的，
  后者表示 expn(i) 在 (i, j) 中经历了若干次清零，最后逐步 +1 得到了 expn(i)。

  据此进行 DP 转移即可。
**********/

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;

  for (int i = 1; i <= N; ++i) {
    u64 x;
    std::cin >> x;
    expn[i] = std::countr_zero(x);
    oddf[i] = x >> expn[i];
  }

  f[0] = f[1] = 0;
  int ans = std::numeric_limits<int>::max();

  for (int i = 2; f[i] = i - 1, i <= N; ans = std::min(ans, f[i] + N - i), ++i)
    for (int j = 1, len = i - 2; j < i; ++j, --len)
      if (oddf[j] % oddf[i] == 0)
        if (expn[i] - expn[j] == len + 1 || expn[i] <= len)
          f[i] = std::min(f[i], f[j] + len);

  std::cout << ans << '\n';
  return 0;
}
