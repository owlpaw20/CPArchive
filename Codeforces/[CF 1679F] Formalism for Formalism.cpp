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

using mint = ModInt<998'244'353>;

const int MAX_N = 50'005;
const int MAX_D = 10;

int N, M;
bool a[MAX_D][MAX_D];
mint f[MAX_N][1 << MAX_D];

// 对于等价的所有串，我们可以用一个代表串来统一表示。
// 因此我们以字典序最小为标准考虑如何判断两串是否等价。
// 显然，如果存在 j > i 且 a[j] < a[i] 且两者可交换，则等价。
// 设 f[i][S] 为，已经填了 i 位数，且 a[i] 不为集合 S 内的数码的方案数

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;

  while (M--) {
    int u, v;
    std::cin >> u >> v;
    a[u][v] = a[v][u] = true;
  }

  f[0][0] = 1;

  for (int i = 0; i <= N; ++i)
    for (int S = 0; S < (1 << MAX_D); ++S)
      if (f[i][S].val())
        for (int j = 0; j < MAX_D; ++j)  // 枚举第 i 位的取值
          if (!(S >> j & 1)) {           // 如果在 S 内合法
            int next = 0;
            for (int k = 0; k < MAX_D; ++k)            // 枚举第 i + 1 位的取值
              if (a[j][k] && (k > j || (S >> k & 1)))  // 如果能交换，但第 i + 1 位大于第 i 位或者已经存在于非法集合 S 中
                next |= 1 << k;                        // 则记入转移后的状态
            f[i + 1][next] += f[i][S];
          }

  std::cout << std::accumulate(f[N], f[N] + (1 << MAX_D), (mint)0).val() << '\n';
  return 0;
}
