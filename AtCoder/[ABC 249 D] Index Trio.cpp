#include <bits/stdc++.h>

const int MAX_N = 2e5 + 5;
const int MAX_V = 2e5;

using LL = long long;

int N, buc[MAX_N];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  for (int i = 1, x; i <= N; ++i) std::cin >> x, ++buc[x];

  LL ans = 0;

  for (int i = 1; i <= MAX_V; ++i)
    for (int j = 1; i * j <= MAX_V; ++j)
      ans += (LL)buc[i] * buc[j] * buc[i * j];

  std::cout << ans << std::endl;
  return 0;
}
