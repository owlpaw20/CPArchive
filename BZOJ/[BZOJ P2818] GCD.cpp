#include <bits/stdc++.h>

using LL = long long;

const int MAX_N = 1e7 + 5;

int N, primes[MAX_N], cnt, phi[MAX_N];
bool flag[MAX_N];
LL sum_phi[MAX_N];

void phi_sieve(int N) {
  phi[1] = 1;

  for (int i = 2; i <= N; ++i) {
    if (!flag[i]) primes[++cnt] = i, phi[i] = i - 1;

    for (int j = 1; j <= cnt; ++j) {
      if (primes[j] * i > N) break;
      flag[primes[j] * i] = true;
      if (i % primes[j] == 0) {
        phi[i * primes[j]] = phi[i] * primes[j];
        break;
      } else
        phi[i * primes[j]] = phi[i] * phi[primes[j]];
    }
  }

  for (int i = 1; i <= N; ++i)
    sum_phi[i] = sum_phi[i - 1] + phi[i];
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  phi_sieve(N);

  LL ans = 0;
  for (int i = 1; i <= cnt; ++i) ans += 2 * sum_phi[N / primes[i]] - 1;

  std::cout << ans << std::endl;
  return 0;
}
