#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned int;

const int MAX_N = 1e5;
const int MAX_C = 4;

int c[MAX_C], d[MAX_C], N;
i64 f[MAX_N + 5];

void solve() {
  for (int i = 0; i < MAX_C; ++i) std::cin >> d[i];
  std::cin >> N;

  i64 ans = 0;

  for (u32 S = 0; S < (1U << MAX_C); ++S) {
    int k = (std::popcount(S) & 1) ? -1 : 1;
    i64 tot = N;

    for (int i = 0; i < MAX_C; ++i)
      if (S >> i & 1)
        tot -= (i64)c[i] * (d[i] + 1);

    if (tot < 0) continue;
    ans += k * f[tot];
  }

  std::cout << ans << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  f[0] = 1;

  for (int i = 0; i < MAX_C; ++i) {
    std::cin >> c[i];
    for (int j = c[i]; j <= MAX_N; ++j)
      f[j] += f[j - c[i]];
  }

  int T;
  std::cin >> T;
  while (T--) solve();

  std::cout.flush();
  return 0;
}
