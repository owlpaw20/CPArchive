#include <vector>
#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;

const int N = 1e7 + 5;

int n;

bool not_prime[N];
vector<int> primes;
int phi[N];
i64 phi_sum[N];

void get_phi(int n) {
  phi[1] = 1;

  for (int i = 2; i <= n; i++) {
    if (!not_prime[i]) {
      primes.push_back(i);
      phi[i] = i - 1;
    }

    for (int j = 0; primes[j] * i <= n; j++) {
      int c = primes[j] * i;
      not_prime[c] = true;

      if (i % primes[j] == 0) {
        phi[c] = phi[i] * primes[j];
        break;
      }

      phi[c] = phi[i] * (primes[j] - 1);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  get_phi(n);

  for (int i = 2; i <= n; i++)
    phi_sum[i] = phi_sum[i - 1] + phi[i];

  i64 ans = 0;
  for (int p : primes)
    ans += phi_sum[n / p] * 2 + 1;

  cout << ans << endl;
  return fflush(stdout), 0;
}
