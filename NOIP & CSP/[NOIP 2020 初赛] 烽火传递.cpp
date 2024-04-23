#include <iostream>
#include <algorithm>

#define endl '\n'

const int MAX_N = 2e5 + 5;
const int INF = 1e9;

int n, m;
int a[MAX_N];

int f[MAX_N];  // f[i] 表示前 i 座烽火台的设置符合条件的情况下，第 i 座烽火台点燃的方案中的最小花费
int q[MAX_N];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> m;
  for (int i = 1; i <= n; ++i) std::cin >> a[i];

  for (int i = 1, qh = 0, qr = 0; i <= n; ++i) {
    if (q[qh] < i - m) ++qh;
    f[i] = f[q[qh]] + a[i];  // f[i] = min_{f[j]} + a[i]
    while (qh <= qr && f[q[qr]] >= f[i]) --qr;
    q[++qr] = i;
  }

  std::cout << *std::min_element(f + n - m + 1, f + n + 1) << endl;
  return fflush(stdout), 0;
}
