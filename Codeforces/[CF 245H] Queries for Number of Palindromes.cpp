#include <bits/stdc++.h>

const int MAX_S = 5e3 + 5;

int N;
std::string s;

bool f[MAX_S][MAX_S];  // f[l][r] 表示 s[l:r] 是否为回文串
int g[MAX_S][MAX_S];   // g[l][r] 表示 s[l:r] 回文串的数量

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> s, N = s.length();
  s = '\0' + s;

  for (int i = 1; i <= N; ++i) {
    g[i][i] = f[i][i] = true;
    f[i - 1][i] = s[i - 1] == s[i];
  }

  // 预处理 f 数组
  for (int len = 3; len <= N; ++len)
    for (int l = 1, r = len; r <= N; ++l, ++r)
      f[l][r] = f[l + 1][r - 1] && s[l] == s[r];

  // 容斥地转移得到 g 数组
  for (int len = 2; len <= N; ++len)
    for (int l = 1, r = len; r <= N; ++l, ++r)
      g[l][r] = g[l + 1][r] + g[l][r - 1] - g[l + 1][r - 1] + f[l][r];

  int q;
  std::cin >> q;

  while (q--) {
    static int l, r;
    std::cin >> l >> r;
    std::cout << g[l][r] << '\n';
  }

  std::cout.flush();
  return 0;
}
