#include <iostream>

using LL = long long;

const int MOD = 1e5 + 3;
const int MAX_N = 2e3 + 5;

int a, b, c, d, K;
int fac[MAX_N], inv[MAX_N];

template <typename intT, typename bufT = LL>
intT power(intT b, intT e, intT mod) {
  intT res = 1;
  while (e) {
    ((e & 1) && (res = (bufT)res * b % mod));
    b = (bufT)b * b % mod;
    e >>= 1;
  }
  return res;
}

void precompute() {
  fac[0] = inv[0] = 1;
  for (int i = 1; i <= (int)2e3; ++i) {
    fac[i] = (LL)fac[i - 1] * i % MOD;
    inv[i] = (LL)inv[i - 1] * power(i, MOD - 2, MOD) % MOD;
  }
}

int nPk(int n, int k) { return (n < k) ? 0 : (LL)fac[n] * inv[n - k] % MOD; }
int nCk(int n, int k) { return (n < k) ? 0 : (LL)fac[n] * inv[k] * inv[n - k] % MOD; }

/****
 * 设上半部分安排 i 个車，则下半部分安排 K - i 个車。
 * 上半部分的 B 行中，选择 i 行安排这 i 个車（这里不需要考虑选择的顺序，車所在列的选择是后面单独考量的，所以用组合数）
 * 在上面的 i 行中，从上往下需要在 A 列中选择 i 列填充（由于需要考虑列内的車放哪一行，而行有上下之分，所以考虑顺序，用排列数）
 * 下半部分的 D 行中，选择 K - i 行安排这 K - i 个車（同理，用组合数）
 * 下半部分一共有 A + C 列，而上半部分的选择占用了其中的 i 列，所以共有 A + C - i 列可供选择
 * 在下面所选的 K - i 行中，从上往下需要在 A + C - i 列中选择 K - i 列填充（同理，用排列数）
 * 用乘法原理整合答案即可。
 ****/

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  precompute();

  std::cin >> a >> b >> c >> d >> K;

  int ans = 0;
  for (int i = 0; i <= K; ++i)
    ans = ((__int128_t)nCk(b, i) * nPk(a, i) * nCk(d, K - i) * nPk(a + c - i, K - i) + ans) % MOD;

  std::cout << ans << std::endl;
  return 0;
}
