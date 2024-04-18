#include <vector>
#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;
using i64 = long long;

const int N = 1e6 + 5;
const int Q = 1e3 + 5;

bool not_prime[N];
vector<int> prime;
int phi[N];
i64 phi_sum[N];

int n;
int q[Q];

void get_phi(int n) {
  phi[1] = 1;

  for (int i = 2; i <= n; i++) {
    if (!not_prime[i]) {
      prime.push_back(i);
      phi[i] = i - 1;
    }

    for (int j = 0; prime[j] * i <= n; j++) {
      int c = prime[j] * i;
      not_prime[c] = true;

      if (i % prime[j] == 0) {
        phi[c] = phi[i] * prime[j];
        break;
      }

      phi[c] = phi[i] * (prime[j] - 1);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;

  int maxq = 0;
  for (int i = 1; i <= n; i++)
    cin >> q[i], maxq = max(maxq, q[i]);

  get_phi(maxq);

  for (int i = 2; i <= maxq; i++)
    phi_sum[i] = phi_sum[i - 1] + phi[i];

  for (int i = 1; i <= n; i++)
    cout << i << ' ' << q[i] << ' ' << phi_sum[q[i]] * 2 + 3 << endl;

  return fflush(stdout), 0;
}
