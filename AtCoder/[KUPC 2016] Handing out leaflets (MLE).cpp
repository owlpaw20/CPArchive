#include <bits/stdc++.h>

template <int MOD>
struct modularInt {
  int v;
  modularInt() : v(0) {}
  template <typename T>
  modularInt(T x) : v((x %= MOD) < 0 ? x + MOD : x) {}
  int val() const { return v; }
  modularInt& operator+=(const modularInt& rhs) { return (v += rhs.v) >= MOD && (v -= MOD), *this; }
  modularInt& operator-=(const modularInt& rhs) { return (v -= rhs.v) < 0 && (v += MOD), *this; }
  modularInt& operator*=(const modularInt& rhs) { return v = int(1LL * v * rhs.v % MOD), *this; }
  modularInt& operator/=(const modularInt& rhs) { return *this *= rhs.inv(); }
  modularInt& operator++() { return ++v >= MOD && (v = 0), *this; }
  modularInt& operator--() { return --v < 0 && (v = MOD - 1), *this; }
  modularInt operator++(int) {
    modularInt temp = *this;
    return ++*this, temp;
  }
  modularInt operator--(int) {
    modularInt temp = *this;
    return --*this, temp;
  }
  modularInt operator-() const { return modularInt(v ? MOD - v : 0); }
  modularInt pow(long long n) const {
    modularInt res(1), x(v);
    for (; n; n >>= 1, x *= x) n & 1 && (res *= x);
    return res;
  }
  modularInt inv() const {
    int a = v, m = MOD, u = 1, t = 0;
    for (int q; m;) q = a / m, a -= q * m, t -= q * u, std::swap(a, m), std::swap(t, u);
    return modularInt(t < 0 ? t + MOD : t);
  }
  friend modularInt operator+(modularInt lhs, const modularInt& rhs) { return lhs += rhs; }
  friend modularInt operator-(modularInt lhs, const modularInt& rhs) { return lhs -= rhs; }
  friend modularInt operator*(modularInt lhs, const modularInt& rhs) { return lhs *= rhs; }
  friend modularInt operator/(modularInt lhs, const modularInt& rhs) { return lhs /= rhs; }
  friend bool operator==(const modularInt& lhs, const modularInt& rhs) { return lhs.v == rhs.v; }
  friend bool operator!=(const modularInt& lhs, const modularInt& rhs) { return lhs.v != rhs.v; }
};

const int MAX_N = 1e5;
const int MAX_SQRT_N = 5e2;

using mint = modularInt<1000000007>;

int N, C;
mint f[MAX_SQRT_N + 5][MAX_N + 5];
mint g[MAX_SQRT_N + 5][MAX_N + 5];

/*************
  最初的状态表示：f[i][j] 表示一个 i 型号机器人在 j 秒内发传单的数量。

  该状态表示下，
    生成机器人，则转移为 f[i][j] <- f[i][j - C * i] + f[i + 1][j - C * i]；
    若只发传单，则转移为 f[i][j] <- f[i][j - 1] + 1；
    答案为 f[1][N]。

  考虑优化。
  我们发现若生成机器人，
  两个机器人在 j 秒内至少可以发 2 * (j - C * i) 张传单，
  如果只发传单则一个机器人同一段时间 j 内可以发 j 张传单。
  因此若 2 * (j - C * i) >= j 时选择生成机器人，否则选择只发传单。
  这是因为，若 2 * (j - C * i) < j，即 j < 2 * C * i，只能生成一次机器人，并且答案较劣。

  为了解决空间问题，我们进一步优化。
  考虑将 2 * (j - C * i) >= j 进一步转化，得到 2 * i <= floor(j / C)。
  可以将状态表示中的 j 改为记录 k = floor(j / C)，此时 f[i][k] 表示原来的 f[i][j]。
  答案表示为 f[i][k] * (N mod C) + g[i][k] * C。
  这里的 f[i][k] 相当于在一整段时间内部，单位为 1 的状态，g[i][k] 则表示单位为一整段时间的状态。

  重写转移式：
    若 2 * i > k，即选择只发传单，则 f[i][k] <- 1, g[i][k] <- k；
    否则，选择生成机器人，f[i][k] <- f[i][k - i] + f[i + 1][k - i]，g[i][k] 转移同理

  由于生成一个 i 型号的机器人至少需要 C * 1 + C * 2 + ... + C * (i - 1) = C * i * (i - 1) / 2 秒，
  所以 i 这一维只需要维护到 O(sqrt(N / C))
**************/

void prep() {
  for (int i = MAX_SQRT_N; i >= 0; --i)
    for (int k = 0; k <= MAX_N; ++k) {
      f[i][k] = (k >= 2 * i) ? f[i][k - i] + f[i + 1][k - i] : 1;
      g[i][k] = (k >= 2 * i) ? g[i][k - i] + g[i + 1][k - i] : k;
    }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  prep();

  int T;
  std::cin >> T;

  while (T--) {
    static int N, C;
    std::cin >> N >> C;
    std::cout << (f[1][N / C] * (N % C) + g[1][N / C] * C).val() << '\n';
  }

  std::cout.flush();
  return 0;
}
