#pragma GCC optimize("O2,unroll-loops,inline")

#include <iostream>

using LL = long long;

const int MAX_N = 25;
const int MOD = 1e9 + 7;

int N, fm = 1;
LL M, f[MAX_N];

template <typename intT, typename bufT = LL>
intT power(intT b, intT e, intT mod) {
  intT res = 1;
  for (; e; e >>= 1)
    ((e & 1) && (res = (bufT)res * b % mod)), b = (bufT)b * b % mod;
  return res;
}

LL nCk(LL n, LL k) {
  if (n < k) return 0;
  int fz = 1;
  for (LL i = n; i > n - k; --i) fz = (LL)i % MOD * fz % MOD;
  return (LL)fz * fm % MOD;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;
  for (int i = 0; i < N; ++i) std::cin >> f[i];

  // 由于组合数的分母是恒定的 N - 1，对其进行预处理
  for (int i = 1; i <= N - 1; ++i) fm = (LL)fm * i % MOD;
  fm = power(fm, MOD - 2, MOD);

  int ans = 0;
  for (int i = 0; i < (1 << N); ++i) {  // 枚举所有花盆中符合条件与否的情况
    LL n = M + N - 1;
    int k = N - 1, sign = 1;

    for (int j = 0; j < N; ++j)
      if ((i >> j) & 1)             // 如果存在一个满足条件的情况
        sign *= -1, n -= f[j] + 1;  // 考虑该情况的容斥系数，以及组合数的底数

    ans = ((LL)ans + nCk(n, k) * sign) % MOD;  // 统计答案
  }

  std::cout << (ans + MOD) % MOD << std::endl;
  return 0;
}
