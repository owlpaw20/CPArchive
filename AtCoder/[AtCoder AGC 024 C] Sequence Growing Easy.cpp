#include <bits/stdc++.h>

using LL = long long;

const int MAX_N = 2e5 + 5;

int N, a[MAX_N];

bool check_invalid() {
  if (a[1]) return true;
  for (int i = 1; i < N; ++i)
    if (a[i + 1] - a[i] > 1)
      return true;
  return false;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  for (int i = 1; i <= N; ++i) std::cin >> a[i];

  if (check_invalid()) return puts("-1"), 0;

  LL ans = 0;

  for (int i = 2; i <= N; ++i)
    if (a[i] == a[i - 1] + 1) ++ans;
    else ans += a[i];

  std::cout << ans << std::flush;
  return 0;
}
