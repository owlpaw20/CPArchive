#include <bits/stdc++.h>

using LL = long long;

const int ANS[] = {0, 4, 10, 20, 35, 56, 83, 116, 155, 198, 244, 292, 341};

int N;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  std::cout << (N <= 12 ? ANS[N] : 341LL + 49LL * (N - 12)) << std::flush;

  return 0;
}
