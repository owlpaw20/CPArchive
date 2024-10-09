#include <bits/stdc++.h>

constexpr int MAX_N = 2e4 + 5;

int N, l[MAX_N], r[MAX_N];
int f[MAX_N][2];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  for (int i = 1; i <= N; ++i) std::cin >> l[i] >> r[i];

  f[1][0] = r[1] - 1 + (r[1] - l[1]);
  f[1][1] = r[1] - 1;

  for (int i = 2; i <= N; ++i) {
    int pl = l[i - 1], pr = r[i - 1], cl = l[i], cr = r[i];
    f[i][0] = std::min(f[i - 1][0] + std::abs(pl - cr) + cr - cl, f[i - 1][1] + std::abs(pr - cr) + cr - cl) + 1;
    f[i][1] = std::min(f[i - 1][0] + std::abs(pl - cl) + cr - cl, f[i - 1][1] + std::abs(pr - cl) + cr - cl) + 1;
  }

  std::cout << std::min(f[N][0] + N - l[N], f[N][1] + N - r[N]) << std::flush;
  return 0;
}
