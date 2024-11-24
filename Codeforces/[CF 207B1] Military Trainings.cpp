#include <bits/stdc++.h>

const int MAX_N = 305;

int N, a[MAX_N << 1], b[MAX_N];
int f[MAX_N];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  for (int i = 1; i <= N; ++i) std::cin >> a[i], a[i + N] = a[i];

  int ans = 0;

  for (int i = 1; i <= N; ++i) {
    for (int j = 0; j < N; ++j) b[j + 1] = a[i + j];
    memset(f, 0x3F, sizeof(int) * (N + 1));
    f[1] = 0;

    for (int j = 2; j <= N; ++j)
      for (int k = std::max(1, j - b[j]); k < j; ++k)
        f[j] = std::min(f[j], f[k] + 1);

    ans += f[N];
  }

  std::cout << ans << '\n';
  return 0;
}
