#include <bits/stdc++.h>

const int MAX_N = 2e6 + 5;

int N, M, s[MAX_N];
std::string s1, s2;

void solve() {
  std::cin >> N >> M >> s1 >> s2;
  for (int i = 0; i < N; ++i) s[i + 1] = ((s1[i] - '0') << 1) + (s2[i] - '0');

  int ans = 0;

  // 第一种策略：youyou 选所有黑白列
  for (int i = 1, sum = 0; i <= N; ++i) {
    if (s[i] == 3) sum += 2;    // 全黑列上下都选，答案 + 2
    else if (s[i] == 0) --sum;  // 全白列只选一个，答案 - 1
    ans = std::max(ans, sum);
    sum = std::max(sum, 0);  // 如果答案已经为负数，则抛弃之并从一个新连通块开始计算
  }

  // 第二种策略：youyou 再在每个黑白列只选择一个格子
  for (int i = 1, sum = 0, last = 3; i <= N; ++i) {
    // 全白列只选一个，具体选哪一个可以由以后的列需要哪一个来维护连通性来决定
    if (s[i] == 0) --sum;

    // 全黑列两个都选并标记，以便以后的列转移
    else if (s[i] == 3) last = 3, sum += 2;

    // 黑白列则优先考虑维护连通性
    // 如果为了连通性所选的那个格子是黑色，那么当前列只需要选这个格子，答案 + 1
    // 否则如果为了连通性选择了当前列白色的格子，那么不如把黑色的也选上，让答案不至于减少
    else if (s[i] == 2) last & 2 ? (last = 2, ++sum) : last = 3;
    else if (s[i] == 1) last & 1 ? (last = 1, ++sum) : last = 3;

    // yy 可以翻转最多 m 个只选一个黑色格子的列，且每翻转一列答案 - 2
    // 所以 youyou 必须要在超过 2m 个黑白列只选择一个格子才能使答案更优
    ans = std::max(ans, sum - 2 * M);

    // 如果答案已经为负数，则抛弃之并从一个新连通块开始计算
    if (sum <= 0) sum = 0, last = 3;
  }

  std::cout << ans << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T >> T;
  while (T--) solve();

  std::cout.flush();
  return 0;
}
