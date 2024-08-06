#include <bits/stdc++.h>

using LL = long long;

const int MAX_N = 1e5 + 5;

int N, M;
LL cnt[MAX_N];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;

  if (N > M) std::swap(N, M);

  for (int i = N; i; --i) {
    cnt[i] = (LL)(N / i) * (M / i);
    for (int j = 2; i * j <= N; ++j) cnt[i] -= cnt[i * j];
  }

  LL ans = 0;
  for (int i = 1; i <= N; ++i) ans += cnt[i] * (i * 2 - 1);

  std::cout << ans << std::flush;
  return 0;
}
