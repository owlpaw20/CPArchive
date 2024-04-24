#include <string>
#include <cstring>
#include <iostream>

#define endl '\n'

const int MAX_N = 55;

int f[MAX_N][MAX_N];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string s;
  std::cin >> s;

  int n = s.length();
  s = '\0' + s;

  memset(f, 0x7F, sizeof f);
  for (int i = 1; i <= n; ++i) f[i][i] = 1;

  for (int len = 2; len <= n; ++len)
    for (int i = 1, j = len; j <= n; ++i, ++j)
      if (s[i] == s[j])
        f[i][j] = std::min(f[i + 1][j], f[i][j - 1]);
      else
        for (int k = i; k <= j; ++k)
          f[i][j] = std::min(f[i][j], f[i][k] + f[k + 1][j]);

  std::cout << f[1][n] << endl;
  fflush(stdout);
  return 0;
}
