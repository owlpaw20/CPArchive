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

void prep() {
  for (int i = MAX_SQRT_N; i >= 0; --i)
    for (int k = 0; k <= MAX_N; ++k)
      f[i][k] = (k >= 2 * i) ? f[i][k - i] + f[i + 1][k - i] : k;
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
    std::cout << (f[1][N / C] * C + (f[1][N / C + 1] - f[1][N / C]) * (N % C)).val() << '\n';
  }

  std::cout.flush();
  return 0;
}
