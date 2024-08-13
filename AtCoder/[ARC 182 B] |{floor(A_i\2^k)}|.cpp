#include <bits/stdc++.h>

int N, K;

void solve() {
  std::cin >> N >> K;

  for (int i = 1, val = 0; i < N * 2; i += 2, val = 0) {
    for (int j = 0; j < K; ++j) (i >> j & 1) && (val |= 1 << (K - j - 1));
    std::cout << val << ' ';
  }

  std::cout.put('\n');
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
