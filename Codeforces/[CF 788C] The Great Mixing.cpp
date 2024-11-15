#pragma GCC optimize("O2,unroll-loops")
#include <bits/stdc++.h>

const int MAX_N = 1e6 + 5;
const int MAX_V = 5e5;
const int OFS = 1e6;
const int INF = 0x3F3F3F3F;

int N, k;
int a[MAX_N], f[MAX_N << 2];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> k >> N;
  for (int i = 1; i <= N; ++i) std::cin >> a[i], a[i] -= k;

  std::sort(a + 1, a + N + 1);
  N = std::unique(a + 1, a + N + 1) - a - 1;

  memset(f, 0x3F, sizeof f);
  for (int i = 1; i <= N; ++i) f[a[i] + OFS] = 1;

  for (int i = 1; i <= N; ++i)
    if (a[i] >= 0)
      for (int j = -MAX_V + OFS; j <= MAX_V + OFS; ++j)
        f[j] = std::min(f[j], f[j - a[i]] + 1);
    else
      for (int j = MAX_V + OFS; j >= -MAX_V + OFS; --j)
        f[j] = std::min(f[j], f[j - a[i]] + 1);

  std::cout << (f[OFS] == INF ? -1 : f[OFS]) << std::flush;
  return 0;
}
