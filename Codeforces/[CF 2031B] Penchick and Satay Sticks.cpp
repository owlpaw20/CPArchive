#include <bits/stdc++.h>

void solve() {
  static int N;
  std::vector<int> a;

  std::cin >> N;
  a.resize(N + 1);
  for (int i = 1; i <= N; ++i) std::cin >> a[i];

  for (int i = 1; i <= N; ++i) {
    if (a[i] == i) continue;
    if (i < N && a[i] == i + 1 && a[i + 1] == i) std::swap(a[i], a[i + 1]);
    else return std::cout << "NO" << '\n', void();
  }

  std::cout << "YES" << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) solve();

  return 0;
}
