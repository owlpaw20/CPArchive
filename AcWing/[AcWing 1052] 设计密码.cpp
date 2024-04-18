// 参考题解：https://www.acwing.com/solution/content/55449/

#include <string>
#include <cstdint>
#include <iostream>

#define endl '\n'

using str = std::string;

const int MAX_N = 55;
const int MOD = 1e9 + 7;

int N;
str T;

struct KMP {
  str pattern;
  int pi[MAX_N];

  void build(str pat) {
    pattern = pat;
    int len = pat.length();
    for (int i = 1, j = 0; i < len; ++i) {
      while (j > 0 && pat[i] != pat[j]) j = pi[j - 1];
      if (pat[i] == pat[j]) ++j;
      pi[i] = j;
    }
  }
} kmp;

// f[i][j] = 长度为 i 的密码，且后缀与模式串匹配的最大长度为 j 的方案数
int f[MAX_N][MAX_N];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> T;
  int M = T.length();

  kmp.build(T);

  f[0][0] = 1;

  for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j)
      for (int c = 'a', p = j; c <= 'z'; ++c) {
        while (p > 0 && c != T[p]) p = kmp.pi[p - 1];
        if (c == T[p]) ++p;
        f[i + 1][p] = (f[i + 1][p] + f[i][j]) % MOD;
        p = j;
      }

  int ans = 0;
  for (int i = 0; i < M; ++i)
    ans = (ans + f[N][i]) % MOD;

  std::cout << ans << endl;
  return fflush(stdout), 0;
}
