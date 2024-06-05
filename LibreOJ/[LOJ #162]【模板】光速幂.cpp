#include <iostream>

using i64 = long long;

const int MOD = 998244352;
const int SQRTMOD = 31959;
const int MAX_SQRT = SQRTMOD + 5;

int X, N, Q;
int below[MAX_SQRT], multi[MAX_SQRT];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> X >> N;

  below[0] = multi[0] = 1;
  for (int i = 1; i <= SQRTMOD; ++i)
    below[i] = (i64)below[i - 1] * X % MOD;
  for (int i = 1; i <= SQRTMOD + 1; ++i)
    multi[i] = (i64)multi[i - 1] * below[SQRTMOD] % MOD;

  while (N--) {
    std::cin >> Q;
    std::cout << (i64)below[Q % SQRTMOD] * multi[Q / SQRTMOD] % MOD << ' ';
  }

  std::cout << std::endl;
  return 0;
}
