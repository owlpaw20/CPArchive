#include <string>
#include <iostream>

#define endl '\n'

const int MAX_N = 2e3 + 5;

std::string s;
bool f[MAX_N][MAX_N];  // 0 = Alice 必胜，1 = 平局

void solve() {
  std::cin >> s;
  int N = s.length();
  s.insert(s.begin(), '\n');

  // 预处理初始情况
  for (int i = 1; i < N; ++i) f[i][i + 1] = s[i] == s[i + 1];

  for (int len = 4; len <= N; len += 2)  // 只有偶数长度区间有用
    for (int l = 1, r = len; r <= N; ++l, ++r)
      // 如果区间首尾相等且内部平局，则当前区间内 Bob 可以取首尾 Alice 没有取的那个字符来打成平局
      if (s[l] == s[r] && f[l + 1][r - 1]) f[l][r] = true;
      // 如果区间首尾不相等，则 Bob 需要从 Alice 选后的首尾中选取一个相同字符并且剩下区间也为平局才能打成平局
      else f[l][r] = s[l] == s[l + 1] && f[l + 2][r] && s[r] == s[r - 1] && f[l][r - 2];

  std::cout << (f[1][N] ? "Draw" : "Alice") << endl;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) solve();

  return fflush(stdout), 0;
}
