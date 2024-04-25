#include <iostream>

#define endl '\n'

using l64 = long long int;
using PII = std::pair<int, int>;

const int MAX_N = 1e3 + 5;

int n, m;
char a[MAX_N][MAX_N];
int up[MAX_N][MAX_N];

PII stack[MAX_N];

inline l64 solve(int r) {
  l64 ans = 0;

  for (int i = 1, width, top = -1; i <= m + 1; ++i) {
    width = 0;
    while (~top && stack[top].second >= up[r][i]) {
      width += stack[top].first;
      ans = std::max(ans, (l64)stack[top--].second * width);
    }
    stack[++top] = PII(width + 1, up[r][i]);
  }

  return ans;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> m;

  bool f_exists = false;

  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) {
      std::cin >> a[i][j], f_exists |= (a[i][j] == 'F');
      up[i][j] = (a[i][j] == 'R') ? 0 : up[i - 1][j] + 1;
    }

  l64 ans = 0;

  if (f_exists)
    for (int i = 1; i <= n; ++i)
      ans = std::max(ans, solve(i));

  std::cout << ans * 3 << endl;
  fflush(stdout);
  return 0;
}
