#include <bits/stdc++.h>

using i64 = long long;

const int MAX_N = 250'005;

int N, a[MAX_N << 1];

struct SpTbl {
  int min[20][MAX_N << 1];

  void build() {
    for (int i = 1; i <= N + N; ++i) min[0][i] = i;
    for (int i = 1; i < 20; ++i)
      for (int j = 1; j + (1 << i) - 1 <= N + N; ++j) {
        bool flag = a[min[i - 1][j]] <= a[min[i - 1][j + (1 << (i - 1))]];
        min[i][j] = flag ? min[i - 1][j] : min[i - 1][j + (1 << (i - 1))];
      }
  }

  int qry(int l, int r) {
    int t = std::__lg(r - l + 1);
    bool flag = a[min[t][l]] <= a[min[t][r - (1 << t) + 1]];
    return flag ? min[t][l] : min[t][r - (1 << t) + 1];
  }
} ST;

int bin[20][MAX_N << 1];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  for (int i = 1; i <= N; ++i) std::cin >> a[i], a[i + N] = a[i];
  for (int i = 1; i <= N + N; ++i) a[i] = std::max(i - a[i], 1);

  ST.build();

  for (int i = 1; i <= N + N; ++i) bin[0][i] = ST.qry(a[i], i);
  for (int i = 1; i < 20; ++i)
    for (int j = 1; j <= N + N; ++j)
      bin[i][j] = bin[i - 1][bin[i - 1][j]];

  i64 ans = 0;

  for (int i = 1; i <= N; ++i) {
    int p = i + N - 1;
    if (a[p] <= i) ++ans;  // 特判起点可以直接到终点的情况
    else {
      ans += 2;
      // 倍增只处理了第一个中间点和最后一个中间点之间的贡献
      // 所以需要加上从起点到第一个中间点及最后一个中间点到终点的贡献
      for (int j = 19; ~j; --j)
        if (a[bin[j][p]] > i)
          ans += (1 << j), p = bin[j][p];
    }
  }

  std::cout << ans << '\n';
  return 0;
}
