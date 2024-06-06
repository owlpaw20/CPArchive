#include <iostream>

using LL = long long;

const int MAX_N = 15;

int N;
int a[MAX_N], b[MAX_N];

void exgcd(LL a, LL b, LL& x, LL& y) {
  if (b == 0) return x = 1, y = 0, void();
  exgcd(b, a % b, y, x);
  y -= a / b * x;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;

  LL prod_a = 1;
  for (int i = 1; i <= N; ++i)
    std::cin >> a[i] >> b[i], prod_a *= a[i];

  LL ans = 0;
  for (int i = 1; i <= N; ++i) {
    LL m_i = prod_a / a[i], x = 0, y = 0;
    exgcd(m_i, a[i], x, y), x = (x < 0 ? x + a[i] : x);
    ans = (ans + (__int128_t)m_i * x * b[i]) % prod_a;
  }

  std::cout << ans << std::endl;
  return 0;
}
