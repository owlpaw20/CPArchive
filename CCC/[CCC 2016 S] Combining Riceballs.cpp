#include <iostream>

#define endl '\n'

const int MAX_N = 4e2 + 5;

int n, a[MAX_N];
int f[MAX_N][MAX_N];  // f[i][j] 表示区间 [i, j] 内的饭团合并之后的大小

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n;
  for (int i = 1; i <= n; ++i) std::cin >> a[i];

  int ans = 0;

  for (int i = 1; i <= n; ++i)
    f[i][i] = a[i], ans = std::max(ans, a[i]);

  for (int len = 2; len <= n; ++len)
    for (int i = 1, j = len; j <= n; ++i, ++j) {
      // 合并相邻两个饭团的情况
      for (int k = i; k < j; ++k)
        if (f[i][k] && f[k + 1][j] && f[i][k] == f[k + 1][j])
          f[i][j] = f[i][k] + f[k + 1][j];

      // 合并三个饭团的情况，由于存在单调性，考虑用双指针维护
      int l = i, r = j;
      while (r - l + 1 >= 3) {
        if (f[i][j]) break;

        if (!f[i][l] || f[i][l] < f[r][j]) ++l;       // 如果左区间合并后太小，则扩大左区间
        else if (!f[r][j] || f[i][l] > f[r][j]) --r;  // 如果右区间合并后太小，则扩大右区间
        else if (f[i][l] == f[r][j]) {                // 如果满足条件则转移
          if (f[l + 1][r - 1]) f[i][j] = f[i][l] + f[l + 1][r - 1] + f[r][j];
          else ++l, --r;  // 否则继续移动指针
        }
      }

      // 统计最大的饭团
      ans = std::max(ans, f[i][j]);
    }

  std::cout << ans << endl;
  fflush(stdout);
  return 0;
}
