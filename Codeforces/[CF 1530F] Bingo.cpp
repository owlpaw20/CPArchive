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

using mint = ModInt<31607>;
using PII = std::pair<int, int>;

const int MAX_N = 25;
const mint INV = mint(10000).inv();

int N;
mint ans;
mint p[MAX_N][MAX_N], row_p[MAX_N];
mint inv_p[MAX_N][MAX_N];

PII col[MAX_N][MAX_N];
int flag[MAX_N][MAX_N];

void DFS(int k, int cnt, mint tot_p) {
  if (k == N + 3) {
    if (!cnt) return;                                      // 如果没有任何一列全为 1，那么无法产生贡献
    for (int i = 1; i <= N; ++i) tot_p *= (1 - row_p[i]);  // 通过各行情况的概率来计算总概率（递归过程中 row_p[i] 数组已经按照情况修改了）
    (cnt & 1) ? ans += tot_p : ans -= tot_p;               // 由于统计保证的是 **至少** 有 cnt 列全为 1，所以需要容斥来获得最终答案
    return;
  }

  // 当前列不全为 1 的情况
  DFS(k + 1, cnt, tot_p);

  // 当前列全为 1 的情况
  for (int i = 1; i <= N; ++i) {
    auto [x, y] = col[k][i];

    if (flag[x][y]) continue;
    flag[x][y] = k;  // 标记 (x, y) 被算在了哪一列的贡献里，避免重复计算

    tot_p *= p[x][y];         // 将 (x, y) 的选择情况算入 tot_p 中
    row_p[x] *= inv_p[x][y];  // 并从 row_p[x] 中删除对应贡献，避免重复计算
  }

  DFS(k + 1, cnt + 1, tot_p);

  // 回溯
  for (int i = 1; i <= N; ++i) {
    auto [x, y] = col[k][i];

    if (flag[x][y] != k) continue;
    flag[x][y] = 0;

    tot_p *= inv_p[x][y];
    row_p[x] *= p[x][y];
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;

  for (int i = 1; i <= N; ++i) {
    row_p[i] = 1;

    for (int j = 1, x; j <= N; ++j) {
      std::cin >> x;
      p[i][j] = x * INV;
      row_p[i] *= p[i][j];
      inv_p[i][j] = p[i][j].inv();
    }
  }

  // 考虑所有存在若干个整行全为 1 的情况
  for (int S = 1; S < (1 << N); ++S) {
    mint tot_p = 1;
    for (int i = 1; i <= N; ++i)
      if (S >> (i - 1) & 1) tot_p *= row_p[i];
      else tot_p *= (1 - row_p[i]);
    ans += tot_p;
  }

  // col[x][y] 表示第 x 列的第 y 个元素的在原矩阵中的位置
  for (int i = 1; i <= N; ++i)
    for (int j = 1; j <= N; ++j)
      col[j][i] = {i, j};

  // 可以将两条对角线也视为两列
  for (int i = 1, j = 1; i <= N; ++i, ++j) col[N + 1][i] = {i, j};
  for (int i = 1, j = N; i <= N; ++i, --j) col[N + 2][i] = {i, j};

  DFS(1, 0, 1);

  std::cout << ans.val() << '\n';
  return 0;
}
