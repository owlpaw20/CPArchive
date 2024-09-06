#include <bits/stdc++.h>

using i64 = long long;

const int MAX_N = 5e5 + 5;
const int MAX_BIT = 30;

int a[MAX_N], hb[MAX_N];
int h_cnt[MAX_BIT + 5];  // 统计 highbit(x) 为定值的数的数量
int s_cnt[MAX_BIT + 5];  // 对于每一个二进制位统计在某一位上为 1 的数的数量

int highbit(int x) {
  for (int i = MAX_BIT; ~i; --i)
    if ((x >> i) & 1)
      return i;
  return -1;
}

void solve() {
  memset(h_cnt, 0, 4 * (MAX_BIT + 1));
  memset(s_cnt, 0, 4 * (MAX_BIT + 1));

  int N;
  std::cin >> N;

  for (int i = 1; i <= N; ++i) {
    std::cin >> a[i];
    hb[i] = highbit(a[i]);

    ++h_cnt[hb[i]];
    for (int j = MAX_BIT; ~j; --j)
      ((a[i] >> j) & 1) && ++s_cnt[j];
  }

  i64 ans = 0;

  // 对于所有数 k，(0 xor k) 都满足 0 <= (0 xor k) <= k

  // 如果以当前数 x 作为较小数，产生贡献当且仅当：
  // - 其他数的 highbit(x) 位上也是 1
  // - 其他数的最高位 != highbit(x)

  for (int i = 1; i <= N; ++i)
    if (!a[i]) ans += N;
    else ans += s_cnt[hb[i]] - h_cnt[hb[i]];

  std::cout << ans << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) solve();

  std::cout.flush();
  return 0;
}
