#include <bits/stdc++.h>

const int MAX_N = 5e2 + 5;

int N, c[MAX_N];
int f[MAX_N][MAX_N];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  for (int i = 1; i <= N; ++i) std::cin >> c[i];

  memset(f, 0x3F, sizeof f);
  for (int i = 1; i <= N; ++i) f[i][i] = 1, f[i - 1][i] = 1 + (c[i - 1] != c[i]);

  for (int len = 3; len <= N; ++len)
    for (int l = 1, r = len; r <= N; ++l, ++r) {
      if (c[l] == c[r]) f[l][r] = std::min(f[l][r], f[l + 1][r - 1]);
      for (int i = l; i < r; ++i) f[l][r] = std::min(f[l][r], f[l][i] + f[i + 1][r]);
    }

  std::cout << f[1][N] << std::flush;
  return 0;
}
