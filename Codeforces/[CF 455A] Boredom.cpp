#include <bits/stdc++.h>

using i64 = long long;

constexpr int MAX_N = 1e5;

int N, cnt[MAX_N + 5];
i64 f[MAX_N + 5][2];  // f[i][0/1] 表示序列中 i 这个数是否被主动删除时的最大得分

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  for (int i = 1, x; i <= N; ++i) std::cin >> x, ++cnt[x];
  // 显然，如果确定了要主动删除一个数，就一定会将所有的这个数都删掉，所以需要对数的出现次数做统计

  for (int i = 1; i <= MAX_N; ++i) {
    // 如果当前数不被主动删除，那么前一个数是否被主动删除都可以
    f[i][0] = std::max(f[i - 1][0], f[i - 1][1]);
    // 如果当前数被主动删除，那么前一个数一定不能被主动删除，并且加上新增的得分
    f[i][1] = f[i - 1][0] + (i64)cnt[i] * i;
  }

  std::cout << std::max(f[MAX_N][0], f[MAX_N][1]) << std::flush;
  return 0;
}
