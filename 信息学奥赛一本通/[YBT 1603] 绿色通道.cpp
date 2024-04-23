#include <iostream>
#include <algorithm>

#define endl '\n'

const int MAX_N = 5e4 + 5;

int n, T;
int a[MAX_N];

int f[MAX_N], q[MAX_N];

inline bool check(int x) {
  f[0] = 0;
  for (int i = 1, qh = 0, qr = 0; i <= n; ++i) {
    if (q[qh] < i - x - 1) ++qh;
    f[i] = f[q[qh]] + a[i];
    while (qh <= qr && f[q[qr]] >= f[i]) --qr;
    q[++qr] = i;
  }

  return *std::min_element(f + n - x, f + n + 1) <= T;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> T;
  for (int i = 1; i <= n; ++i) std::cin >> a[i];

  int l = 0, r = n;
  while (l < r) {
    int mid = (l + r) >> 1;
    if (check(mid)) r = mid;
    else l = mid + 1;
  }

  std::cout << r << endl;
  return fflush(stdout), 0;
}
