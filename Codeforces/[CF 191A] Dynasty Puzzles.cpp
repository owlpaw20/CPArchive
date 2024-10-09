#include <bits/stdc++.h>

constexpr int MAX_C = 26;

int N, f[MAX_C][MAX_C];
// f[i][j] 表示以字母 i 开始 j 结束的最长字符串长度

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  memset(f, -1, sizeof f);

  while (N--) {
    std::string s;
    std::cin >> s;

    int l = s.front() - 'a';
    int r = s.back() - 'a';
    int len = s.length();

    for (int i = 0; i < 26; ++i)  // 尝试从每个字母为开头、s[l] 为结尾的字符串进行转移
      if (f[i][l] != -1)          // 转移前需要判断原状态是否已经存在，否则根据题意不能转移
        f[i][r] = std::max(f[i][r], f[i][l] + len);

    // 注意转移顺序：根据题意，需要在从之前的状态转移过来之后再考虑当前字符串的贡献
    f[l][r] = std::max(f[l][r], len);
  }

  int ans = 0;
  for (int i = 0; i < 26; ++i) ans = std::max(ans, f[i][i]);

  std::cout << ans << std::flush;
  return 0;
}
