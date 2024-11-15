#include <bits/stdc++.h>

const int MAX_N = 2e3 + 5;

int N, max_p, W;
int f[MAX_N][MAX_N];  // f[i][j] 表示第 i 天持有 j 张股票时所赚到的最大钱数

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> max_p >> W;

  memset(f, 0xC0, sizeof f);

  for (int i = 1; i <= N; ++i) {
    static int ap, bp, as, bs;
    std::cin >> ap >> bp >> as >> bs;

    for (int j = 0; j <= as; ++j) f[i][j] = -ap * j;
    for (int j = max_p; ~j; --j) f[i][j] = std::max(f[i][j], f[i - 1][j]);

    if (i - W - 1 >= 0) {
      std::deque<int> q1, q2;

      // 在第 i 天买入 j - k 支股票
      // f[i][j] <- f[i - W - 1][k] - (j - k) * ap <=> f[i - W - 1][k] + (k - j) * ap

      for (int j = 0; j <= max_p; ++j) {
        while (!q1.empty() && f[i - W - 1][q1.back()] + q1.back() * ap <= f[i - W - 1][j] + j * ap) q1.pop_back();
        q1.push_back(j);
        f[i][j] = std::max(f[i][j], f[i - W - 1][q1.front()] - (j - q1.front()) * ap);
        while (!q1.empty() && j - q1.front() >= as) q1.pop_front();
      }

      // 在第 i 天卖出 k - j 支股票
      // f[i][j] <- f[i - W - 1][k] + (k - j) * bp
      // 为了保证所有能转移到 j 的 k 都入队，需要倒序遍历

      for (int j = max_p; ~j; --j) {
        while (!q2.empty() && f[i - W - 1][q2.back()] + q2.back() * bp <= f[i - W - 1][j] + j * bp) q2.pop_back();
        q2.push_back(j);
        f[i][j] = std::max(f[i][j], f[i - W - 1][q2.front()] + (q2.front() - j) * bp);
        while (!q2.empty() && q2.front() - j >= bs) q2.pop_front();
      }
    }
  }

  std::cout << *std::max_element(f[N], f[N] + max_p + 1) << std::flush;
  return 0;
}
