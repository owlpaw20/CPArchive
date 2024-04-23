#include <iostream>

#define endl '\n'

using l64 = long long int;

const int MAX_N = 1e5 + 5;

int n, k;
l64 e[MAX_N], d[MAX_N], f[MAX_N];
int q[MAX_N], qh = 0, qr = 0;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> k;

  for (int i = 1; i <= n; ++i) {
    std::cin >> e[i];
    e[i] += e[i - 1];

    d[i] = f[i - 1] - e[i];
    while (qh <= qr && d[q[qr]] < d[i]) --qr;
    q[++qr] = i;
    while (q[qh] + k < i) ++qh;
    f[i] = d[q[qh]] + e[i];
  }

  std::cout << f[n] << endl;
  return fflush(stdout), 0;
}
