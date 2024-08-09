#include <bits/stdc++.h>

using i64 = long long;
using PII = std::pair<int, int>;

const int MAX_N = 3e3 + 5;

int N;
PII s[MAX_N];
i64 f[MAX_N];  // f[i] 表示第 i 条线段为红色，并且填到第 i 条线段都合法的最小答案

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  for (int i = 1; i <= N; ++i) std::cin >> s[i].first >> s[i].second;
  std::sort(s + 1, s + N + 1);

  // 设置阈值（在转移过程中，如果此前没有任何合法线段，则从 0 转移）
  s[0].second = std::numeric_limits<int>::min();

  i64 ans = std::numeric_limits<i64>::max();
  memset(f, 0x3F, sizeof(i64) * (N + 1)), f[0] = 0;

  for (int i = 1; i <= N; ++i) {
    int maxl = std::numeric_limits<int>::min();
    int l = s[i].first, len = s[i].second - l;

    // 找到不与当前线段相交的线段中的最大左端点
    for (int j = 1; j < i; ++j)
      if (s[j].second < l)
        maxl = std::max(maxl, s[j].first);

    // 对所有的合法线段进行转移
    for (int j = 0; j < i; ++j)
      if (maxl <= s[j].second && s[j].second < l)
        f[i] = std::min(f[i], f[j] + len);

    // 统计答案
    if (s[i].second >= s[N].first) ans = std::min(ans, f[i]);
  }

  std::cout << ans << std::flush;
  return 0;
}
