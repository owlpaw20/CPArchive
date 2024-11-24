#pragma GCC optimize("O2,unroll-loops")
#include <bits/stdc++.h>

template <int MOD>
struct ModInt {
  // clang-format off
  int v;
  ModInt() : v(0) {}
  template <typename T>
  ModInt(T x) : v((x %= MOD) < 0 ? x + MOD : x) {}
  inline int val() const { return v; }
  inline ModInt& operator+=(const ModInt& rhs) { return (v += rhs.v) >= MOD && (v -= MOD), *this; }
  inline ModInt& operator-=(const ModInt& rhs) { return (v -= rhs.v) < 0 && (v += MOD), *this; }
  inline ModInt& operator*=(const ModInt& rhs) { return v = int(1LL * v * rhs.v % MOD), *this; }
  inline ModInt& operator/=(const ModInt& rhs) { return *this *= rhs.inv(); }
  inline ModInt& operator++() { return ++v >= MOD && (v = 0), *this; }
  inline ModInt& operator--() { return --v < 0 && (v = MOD - 1), *this; }
  inline ModInt operator++(int) { ModInt temp = *this; return ++*this, temp; }
  inline ModInt operator--(int) { ModInt temp = *this; return --*this, temp; }
  inline ModInt operator-() const { return ModInt(v ? MOD - v : 0); }
  inline ModInt pow(long long n) const { ModInt res(1), x(v); for (; n; n >>= 1, x *= x) if (n & 1) res *= x; return res; }
  inline ModInt inv() const { return assert(v), pow(MOD - 2); }
  inline friend ModInt operator+(ModInt lhs, const ModInt& rhs) { return lhs += rhs; }
  inline friend ModInt operator-(ModInt lhs, const ModInt& rhs) { return lhs -= rhs; }
  inline friend ModInt operator*(ModInt lhs, const ModInt& rhs) { return lhs *= rhs; }
  inline friend ModInt operator/(ModInt lhs, const ModInt& rhs) { return lhs /= rhs; }
  inline friend bool operator==(const ModInt& lhs, const ModInt& rhs) { return lhs.v == rhs.v; }
  inline friend bool operator!=(const ModInt& lhs, const ModInt& rhs) { return lhs.v != rhs.v; }
  // clang-format on
};

using mint = ModInt<1'000'000'007>;

const int MAX_N = 205;
const int MAX_K = 1005;

int N, K, a[MAX_N];
mint f[MAX_N][MAX_N][MAX_K];

// 显然，分成的组产生的代价只跟最大值和最小值有关，因此可以将 a 排序后只考虑每个分组的端点来处理
// f[i][j][k] 表示排序后，已经处理了 i 个数，还有 j 组只确定了最小值（没有确定最大值），当前已经产生 k 的总贡献

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> K;
  for (int i = 1; i <= N; ++i) std::cin >> a[i];
  std::sort(a + 1, a + N + 1);

  f[0][0][0] = 1;

  for (int i = 0; i <= N; ++i)
    for (int j = 0; j <= N; ++j)
      for (int k = 0; k <= K; ++k)
        if (f[i][j][k].val()) {
          int c = j * (a[i + 1] - a[i]);  // 迭代计算新增一个元素对无最大值的 j 组带来的总代价
          if (k + c > K) continue;
          f[i + 1][j][k + c] += f[i][j][k];                 // 新开一组，成为其最小值且成为其最大值
          f[i + 1][j][k + c] += f[i][j][k] * j;             // 进入某一无最大值的组，且不成为最大值
          f[i + 1][j + 1][k + c] += f[i][j][k];             // 新开一组，成为其最小值且不成为最大值
          if (j) f[i + 1][j - 1][k + c] += f[i][j][k] * j;  // 进入某一无最大值的组，且成为其最大值
        }

  std::cout << std::accumulate(f[N][0], f[N][0] + K + 1, (mint)0).val() << '\n';
  return 0;
}
