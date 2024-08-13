#include <bits/stdc++.h>

const int MAX_N = 5e3 + 5;
const int MOD = 998'244'353;

int N, q, p[MAX_N], v[MAX_N];
bool ok[MAX_N][2];  // ok[i][0] 表示第 i 次操作是否可以向左，ok[i][1] 表示是否可以向右

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> q;

  for (int i = 1; i <= q; ++i) {
    std::cin >> p[i] >> v[i];
    ok[i][0] = ok[i][1] = true;
  }

  for (int i = 1; i <= q; ++i)
    for (int j = i + 1; j <= q; ++j) {
      if (v[i] <= v[j]) continue;
      if (p[i] > p[j]) ok[i][0] = ok[j][1] = false;
      else if (p[i] < p[j]) ok[i][1] = ok[j][0] = false;
      else ok[i][0] = ok[i][1] = ok[j][0] = ok[j][1] = false;
    }

  int ans = 1;
  for (int i = 1; i <= q; ++i) ans = ans * (ok[i][0] + ok[i][1]) % MOD;

  std::cout << ans << std::flush;
  return 0;
}
