#include <bits/stdc++.h>

using i64 = long long;

const int MOD = 998'244'353;
const int HALF = 499'122'177;

int a, b, k;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> a >> b >> k;

  int ans = 1;

  for (int i = 1; i <= k; ++i) {
    if (i % a == 0) ans = (i64)ans * 2 % MOD;
    if (i % b == 0) ans = (ans == 1) ? 1 : (i64)ans * HALF % MOD;
  }

  std::cout << ans << std::flush;
  return 0;
}
