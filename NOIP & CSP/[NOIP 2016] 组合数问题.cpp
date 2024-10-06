#include <bits/stdc++.h>

using i64 = long long;

const int MAX_N = 2e3;

int T, k;
int b[MAX_N + 5][MAX_N + 5];
int s[MAX_N + 5][MAX_N + 5];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> T >> k;

  b[0][0] = 1;

  for (int i = 1; i <= MAX_N; ++i)
    for (int j = 0; j <= i; ++j)
      b[i][j] = (j && j ^ i) ? (b[i - 1][j - 1] + b[i - 1][j]) % k : 1;

  for (int i = 1; i <= MAX_N; ++i)
    for (int j = 1; j <= MAX_N; ++j)
      s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + (!b[i][j] && j <= i);

  while (T--) {
    static int a, b;
    std::cin >> a >> b;
    std::cout << s[a][b] << '\n';
  }

  std::cout.flush();
  return 0;
}
