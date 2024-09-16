#include <bits/stdc++.h>

using i64 = long long;

const int MAX_BIT = 30;

i64 f[MAX_BIT + 5][2][2];

// pos 为当前位，a_lmt 和 b_lmt 分别表示在当前位上 a 和 b 取值是否受限
i64 DFS(int l, int r, int pos = MAX_BIT, bool a_lmt = true, bool b_lmt = true) {
  if (pos == -1) return 1;  // 统计到合法的状态

  // 状态已经记忆化了
  if (f[pos][a_lmt][b_lmt] != -1) return f[pos][a_lmt][b_lmt];

  i64 ans = 0;

  int a = a_lmt ? (l >> pos & 1) : 1;  // 如果 a 当前位仍受限，取 l 当前位的值作枚举上限
  int b = b_lmt ? (r >> pos & 1) : 1;  // 如果 b 当前位仍受限，取 r 当前位的值作枚举上限

  // 以 a_lmt、i 和 a 为例：
  // a_lmt = false，则当前位及以下都不受限
  // a_lmt = true，则若 i 枚举至上限 a，下一位依然受限，否则当前位以下都不受限

  for (int i = 0; i <= a; ++i)
    for (int j = 0; j <= b; ++j)
      if (!(i & j))  // 如果在限制范围内满足这一位上 a and b = 0 则递归到下一位
        ans += DFS(l, r, pos - 1, a_lmt && (i == a), b_lmt && (j == b));

  return f[pos][a_lmt][b_lmt] = ans;  // 记忆化
}

void solve() {
  int L, R;
  std::cin >> L >> R;

  // foo(L, R) 表示当 a in [0, L] 且 b in [0, R] 时满足 a & b = 0 的正整数对数
  auto foo = [&](int l, int r) -> i64 {
    if (l < 0 || r < 0) return 0;
    memset(f, -1, sizeof f);
    return DFS(l, r);
  };

  // 通过容斥计算满足 a,b in [L, R] 时满足 a & b = 0 的正整数对数
  std::cout << foo(R, R) - foo(L - 1, R) - foo(R, L - 1) + foo(L - 1, L - 1) << '\n';
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
