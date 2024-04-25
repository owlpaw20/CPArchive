#include <iostream>

#define endl '\n'

const int MAX_N = 1e3 + 5;

int n, m;
char a[MAX_N][MAX_N];

int vert[MAX_N][MAX_N];
int l[MAX_N][MAX_N], r[MAX_N][MAX_N];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> m;

  bool f_exists = false;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      std::cin >> a[i][j];
      l[i][j] = r[i][j] = j;
      vert[i][j] = 1;

      f_exists |= (a[i][j] == 'F');
    }

    // 更新每个点能向左延长到的最远格
    for (int j = 2; j <= m; ++j)
      if (a[i][j] == 'F' && a[i][j - 1] == 'F')
        l[i][j] = l[i][j - 1];

    // 更新每个点能向右延长到的最远格
    for (int j = m - 1; j; --j)
      if (a[i][j] == 'F' && a[i][j + 1] == 'F')
        r[i][j] = r[i][j + 1];
  }

  if (!f_exists)
    std::cout << 0 << endl;
  else {
    int ans = 1;
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j) {
        if (i > 1 && a[i][j] == 'F' && a[i - 1][j] == 'F') {
          vert[i][j] = vert[i - 1][j] + 1;           // 更新每个点能向上延长的最远格
          l[i][j] = std::max(l[i][j], l[i - 1][j]);  // 挤压左边界
          r[i][j] = std::min(r[i][j], r[i - 1][j]);  // 挤压右边界
        }

        // 统计最优解
        ans = std::max(ans, (r[i][j] - l[i][j] + 1) * vert[i][j]);
      }

    std::cout << ans * 3 << endl;
  }

  fflush(stdout);
  return 0;
}
