#include <bits/stdc++.h>

const int MAX_N = 1e5 + 5;

int N, a[MAX_N];
std::map<int, int> map;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  for (int i = 1; i <= N; ++i) std::cin >> a[i], ++map[a[i]];

  int remaining = 0;
  for (auto [x, cnt] : map) remaining = std::max(remaining, cnt);

  std::cout << remaining << std::flush;
  return 0;
}
