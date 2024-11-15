#include <bits/stdc++.h>

using i64 = long long;

const int MAX_N = 5e5 + 5;
const int MAX_K = 1e2 + 5;

int N, k, p;
int a[MAX_N], sum[MAX_N];

int f[MAX_N][MAX_K];    // f[i][j] 表示前 i 个数分成 j 段的最小答案
int pos[MAX_N][MAX_K];  // pos[i][j] 表示上述状态的最优转移值

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> k >> p;

  for (int i = 1; i <= N; ++i) {
    std::cin >> a[i];
    sum[i] = (sum[i - 1] + a[i]) % p;
  }

  memset(f, 0x3F, sizeof f);
  f[0][0] = 0;

  for (int j = 1; j <= k; ++j) {
    pos[0][j] = 0;

    for (int i = 1; i <= N; ++i)
      if (f[pos[i - 1][j]][j - 1] > f[i][j - 1]) pos[i][j] = i;
      else pos[i][j] = pos[i - 1][j];

    for (int i = j; i <= N; ++i)
      f[i][j] = f[pos[i - 1][j]][j - 1] + (sum[i] - sum[pos[i - 1][j]] + p) % p;
  }

  std::cout << f[N][k] << std::flush;
  return 0;
}
