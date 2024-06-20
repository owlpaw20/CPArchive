#include <iostream>

using LL = long long;

const int MAX_N = 2e5 + 5;
const int MOD = 998244353;

int N;
int exp10[MAX_N] = {1};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  for (int i = 1; i <= N; ++i)
    exp10[i] = 10LL * exp10[i - 1] % MOD;

  for (int i = 1; i <= N; ++i)
    if (i == N) std::cout << 10 << std::endl;
    else std::cout << (18LL * exp10[N - i] + 81LL * (N - i - 1) * exp10[N - i - 1]) % MOD << ' ';

  return 0;
}
