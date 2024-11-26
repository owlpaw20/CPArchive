#include <bits/stdc++.h>

using i64 = long long;

const int MAX_N = 1005;
const int MAX_M = 55;

int N, M, K;
std::string c, s, t;
int nextS[MAX_M][26], nextT[MAX_M][26];

// 预处理 KMP DFA
void prep(std::string s, int N, int next[][26]) {
  std::vector<int> pi(N + 1);
  pi[1] = 0;

  for (int i = 2; i <= N; ++i) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j + 1]) j = pi[j];
    if (s[i] == s[j + 1]) ++j;
    pi[i] = j;
  }

  for (int i = 0; i <= N; ++i)
    for (int j = 0; j < 26; ++j) {
      int p = i;
      while (p > 0 && s[p + 1] - 'a' != j) p = pi[p];
      if (s[p + 1] - 'a' == j) ++p;
      next[i][j] = p;
    }
}

int f[MAX_N][MAX_M][MAX_M];
// f[i][j][k] 表示考虑 c 的第 i 位，此时 s 和 t 的 KMP 状态分别匹配到第 j 和 k 位的最大答案

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> c >> s >> t;
  N = c.length(), M = s.length(), K = t.length();
  c = '\0' + c, s = '\0' + s, t = '\0' + t;

  prep(s, M, nextS);
  prep(t, K, nextT);

  memset(f, 0xC0, sizeof f);
  f[0][0][0] = 0;

  for (int i = 0; i < N; ++i)
    for (int j = 0; j <= M; ++j)
      for (int k = 0; k <= K; ++k)
        for (int l = 0; l < 26; ++l)
          if (c[i + 1] == '*' || c[i + 1] - 'a' == l) {
            int nxS = nextS[j][l], nxT = nextT[k][l];
            f[i + 1][nxS][nxT] = std::max(f[i + 1][nxS][nxT], f[i][j][k] + (nxS == M) - (nxT == K));
          }

  int ans = std::numeric_limits<int>::min();

  for (int i = 0; i <= M; ++i)
    for (int j = 0; j <= K; ++j)
      ans = std::max(ans, f[N][i][j]);

  std::cout << ans << '\n';
  return 0;
}
