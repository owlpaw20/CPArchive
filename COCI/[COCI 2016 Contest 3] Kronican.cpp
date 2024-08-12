#include <bits/stdc++.h>

const int MAX_N = 25;
const int MAX_ST = 1 << 20;

int N, K;
int c[MAX_N][MAX_N];
int f[MAX_ST];  // 0 = 没有倒走，1 = 已经倒走

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> K;

  for (int i = 1; i <= N; ++i)
    for (int j = 1; j <= N; ++j)
      std::cin >> c[i][j];

  memset(f, 0x3F, sizeof(int) * (1 << N));
  f[0] = 0;

  int ans = std::numeric_limits<int>::max();

  for (int S = 0; S < (1 << N); ++S) {
    int popcnt = 0;
    for (int i = 0; i < N; ++i)  // 枚举被倒走的位置
      if ((S >> i & 1) && ++popcnt)
        for (int j = 0; j < N; ++j)  // 枚举被倒到的位置
          if (!(S >> j & 1))
            f[S] = std::min(f[S], f[S ^ (1 << i)] + c[i + 1][j + 1]);

    if (N - popcnt <= K) ans = std::min(ans, f[S]);
  }

  std::cout << ans << std::flush;
  return 0;
}
