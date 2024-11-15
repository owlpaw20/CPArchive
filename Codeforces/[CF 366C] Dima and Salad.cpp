#include <bits/stdc++.h>

const int MAX_N = 1e2 + 5;
const int MAX_V = 1e4 + 5;

int N, k, a[MAX_N], b[MAX_N];
int f[MAX_V], g[MAX_V];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> k;
  for (int i = 1; i <= N; ++i) std::cin >> a[i];
  for (int i = 1; i <= N; ++i) std::cin >> b[i];

  memset(f, 0xC0, sizeof f);
  memset(g, 0xC0, sizeof g);
  f[0] = g[0] = 0;

  for (int i = 1, w; i <= N; ++i)
    if ((w = a[i] - b[i] * k) >= 0)
      for (int j = MAX_V - 5; j >= w; --j)
        f[j] = std::max(f[j], f[j - w] + a[i]);
    else
      for (int j = MAX_V - 5; j >= -w; --j)
        g[j] = std::max(g[j], g[j + w] + a[i]);

  int ans = 0;
  for (int i = 0; i <= MAX_V - 5; ++i) ans = std::max(ans, f[i] + g[i]);
  std::cout << (ans ? ans : -1) << std::flush;
  return 0;
}
