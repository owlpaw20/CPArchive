#include <bits/stdc++.h>

using i64 = long long;

const int MAX_N = 3e3 + 5;
const int MAX_H = 25;
const int MOD = 1e9;

int N, ans[MAX_N];
int f[MAX_N][MAX_H];  // f[i][j] 表示有 i 个节点且高度为 j 的 AVL 树的数量

void prep() {
  f[0][0] = 1;

  for (int i = 1; i <= 3000; ++i)
    for (int j = 1; j <= 20; ans[i] = (ans[i] + f[i][j++]) % MOD)
      for (int k = 0; k < i; ++k) {
        f[i][j] = (f[i][j] + (i64)f[k][j - 1] * f[i - 1 - k][j - 1]) % MOD;
        f[i][j] = (f[i][j] + (i64)f[k][j - 1] * f[i - 1 - k][j - 2] * 2) % MOD;
      }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  prep();

  while (std::cin >> N, N)
    if (N < 35) std::cout << ans[N] << '\n';
    else std::cout << std::setfill('0') << std::setw(9) << ans[N] << '\n';

  std::cout.flush();
  return 0;
}
