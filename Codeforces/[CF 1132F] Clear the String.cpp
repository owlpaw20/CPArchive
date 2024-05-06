#include <iostream>

#define endl '\n'

const int MAX_N = 5e2 + 5;
const int INF = 2e9;

int N;
char s[MAX_N];
int f[MAX_N][MAX_N];  // f[i][j] 表示消除区间 i 到 j 所需要的最小次数

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  for (int i = 1; i <= N; ++i) std::cin >> s[i];

  for (int i = 1; i <= N; ++i) f[i][i] = 1;

  for (int len = 2; len <= N; ++len)
    for (int l = 1, r = len; r <= N; ++l, ++r) {
      // 如果 l 单独删除
      f[l][r] = f[l + 1][r] + 1;

      // 如果 l 与其他字符一起删除
      for (int i = l + 1; i <= r; ++i)
        if (s[l] == s[i])                                          // 枚举 l 后的与之相同的字符
          f[l][r] = std::min(f[l][r], f[l + 1][i - 1] + f[i][r]);  // 统计消除相同字符之间的开销和消除后方字符的开销
    }

  std::cout << f[1][N] << endl;
  return fflush(stdout), 0;
}
