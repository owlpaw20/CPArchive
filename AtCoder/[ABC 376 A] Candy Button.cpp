#include <bits/stdc++.h>

const int MAX_N = 1e3 + 5;

int N, C, T[MAX_N];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> C;
  int ans = 0, lastT = -1;

  for (int i = 1; i <= N; ++i) {
    std::cin >> T[i];
    if (lastT < 0) ++ans, lastT = T[i];
    else if (T[i] - lastT >= C) ++ans, lastT = T[i];
  }

  std::cout << ans << std::flush;
  return 0;
}
