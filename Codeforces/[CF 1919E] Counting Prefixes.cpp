#include <bits/stdc++.h>

template <int MOD>
struct ModInt {
  // clang-format off
  int v;
  ModInt() : v(0) {}
  template <typename T>
  ModInt(T x) : v((x %= MOD) < 0 ? x + MOD : x) {}
  int val() const { return v; }
  ModInt& operator+=(const ModInt& rhs) { return (v += rhs.v) >= MOD && (v -= MOD), *this; }
  ModInt& operator-=(const ModInt& rhs) { return (v -= rhs.v) < 0 && (v += MOD), *this; }
  ModInt& operator*=(const ModInt& rhs) { return v = int(1LL * v * rhs.v % MOD), *this; }
  ModInt& operator/=(const ModInt& rhs) { return *this *= rhs.inv(); }
  ModInt& operator++() { return ++v >= MOD && (v = 0), *this; }
  ModInt& operator--() { return --v < 0 && (v = MOD - 1), *this; }
  ModInt operator++(int) { ModInt temp = *this; return ++*this, temp; }
  ModInt operator--(int) { ModInt temp = *this; return --*this, temp; }
  ModInt operator-() const { return ModInt(v ? MOD - v : 0); }
  ModInt pow(long long n) const { ModInt res(1), x(v); for (; n; n >>= 1, x *= x) if (n & 1) res *= x; return res; }
  ModInt inv() const { return assert(v), pow(MOD - 2); }
  friend ModInt operator+(ModInt lhs, const ModInt& rhs) { return lhs += rhs; }
  friend ModInt operator-(ModInt lhs, const ModInt& rhs) { return lhs -= rhs; }
  friend ModInt operator*(ModInt lhs, const ModInt& rhs) { return lhs *= rhs; }
  friend ModInt operator/(ModInt lhs, const ModInt& rhs) { return lhs /= rhs; }
  friend bool operator==(const ModInt& lhs, const ModInt& rhs) { return lhs.v == rhs.v; }
  friend bool operator!=(const ModInt& lhs, const ModInt& rhs) { return lhs.v != rhs.v; }
  // clang-format on
};

using mint = ModInt<998'244'353>;

const int MAX_N = 5e3 + 5;

int N;
mint fac[MAX_N << 2], ifac[MAX_N << 2];

void prep() {
  fac[0] = ifac[0] = 1;
  for (int i = 1; i <= 10'005; ++i) fac[i] = fac[i - 1] * i;
  for (int i = 1; i <= 10'005; ++i) ifac[i] = ifac[i - 1] / i;
}

mint binom(int n, int k) {
  if (n < k || k < 0) return 0;
  return fac[n] * ifac[k] * ifac[n - k];
}

mint stars_and_bars(int n, int x) {
  if (!n && !x) return 1;
  return binom(x + n - 1, x);
}

void solve() {
  std::cin >> N;
  const int OFS = N + 1;
  std::vector<int> f(N * 2 + 5);

  // 统计每一种前缀和的出现次数，包括 p[0]
  for (int i = 1, x; i <= N; ++i) std::cin >> x, ++f[x + OFS];
  ++f[OFS];

  // 获取出现过的前缀和中的最大值和最小值
  int min = std::numeric_limits<int>::max();
  int max = std::numeric_limits<int>::min();

  for (int i = 0; i <= N + OFS; ++i)
    if (f[i])
      min = std::min(min, i), max = std::max(max, i);

  mint ans = 0;

  // 由于 a 中只能包含 -1 和 1，所以如果最大值等于最小值说明无解
  if (max == min) goto fail;

  // 由于前缀和每次只能变动 1，所以如果最大值到最小值之间存在断点，也无解
  for (int i = min; i <= max; ++i)
    if (!f[i])
      goto fail;

  // 根据构造方法（见官方题解）从拟想的 max = p[N] 进行迭代
  for (int i = max; i >= min; --i) {
    std::vector<int> d(max);  // 反推差分数组
    d[max - 1] = f[max] + (max > OFS) - (max == i);
    for (int j = max - 2; j >= min - 1; --j)
      d[j] = f[j + 1] - d[j + 1] + (j >= i) + (j >= OFS);

    if (!d[min - 1]) {  // 只有 d[p[0]] == 0 时情况合法
      mint res = 1;
      for (int j = max - 1; j >= min; --j)
        res *= stars_and_bars(d[j], f[j] - d[j]);  // 情况数通过插板法计算
      ans += res;
    }
  }

  std::cout << ans.val() << '\n';
  return;

fail:
  std::cout << 0 << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  prep();

  int T;
  std::cin >> T;
  while (T--) solve();

  return 0;
}
