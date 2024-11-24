#include <bits/stdc++.h>

const int MAX_N = 10'005;

int N, a[MAX_N << 1];

struct SpTbl {
  int min[16][MAX_N << 1];

  void build() {
    for (int i = 1; i <= N + N; ++i) min[0][i] = i;
    for (int i = 1; i < 16; ++i)
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

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  for (int i = 1; i <= N; ++i) std::cin >> a[i], a[i + N] = a[i];
  for (int i = 1; i <= N + N; ++i) a[i] = std::max(i - a[i], 1);

  ST.build();
  int ans = 0;

  for (int i = 1; i <= N; ++i, ++ans) {
    int l = a[i + N - 1], r = i + N - 1;
    while (l > i) r = ST.qry(l, r - 1), l = a[r], ++ans;
  }

  std::cout << ans << '\n';
  return 0;
}
