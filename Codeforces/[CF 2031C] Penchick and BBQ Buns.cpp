#include <bits/stdc++.h>

void solve() {
  int N;
  std::cin >> N;

  if (N & 1) {
    if (N <= 25) return std::cout << -1 << '\n', void();
    std::cout << "1 3 3 4 4 5 5 6 6 1 2 7 7 8 8 9 9 10 10 11 11 12 12 13 13 1 2";
    for (int i = 28; i <= N; ++i) std::cout << ' ' << (i >> 1);
    std::cout << '\n';
  }

  else {
    for (int i = 1; i + i <= N; ++i) std::cout << i << ' ' << i << ' ';
    std::cout << '\n';
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) solve();

  return 0;
}
