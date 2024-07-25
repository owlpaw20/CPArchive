#pragma GCC optimize("O2,unroll-loops,inline")

#include <cstring>
#include <iostream>

using LL = long long;
using PII = std::pair<LL, LL>;

constexpr int MAX_N = 1e5 + 5;

int N, a[MAX_N], b[MAX_N], c[MAX_N];
LL pre_c[MAX_N];

struct SparseTable {
  LL max[MAX_N][20], min[MAX_N][20];

  void init() {
    for (int i = 1; i <= N; ++i) max[i][0] = min[i][0] = pre_c[i];
    for (int j = 1; j < 20; ++j)
      for (int i = 1; i + (1 << j) - 1 <= N; ++i) {
        max[i][j] = std::max(max[i][j - 1], max[i + (1 << (j - 1))][j - 1]);
        min[i][j] = std::min(min[i][j - 1], min[i + (1 << (j - 1))][j - 1]);
      }
  }

  PII qry(int l, int r) {
    int t = std::__lg(r - l + 1);
    LL mx = std::max(max[l][t], max[r - (1 << t) + 1][t]);
    LL mn = std::min(min[l][t], min[r - (1 << t) + 1][t]);
    return {mx, mn};
  }
} ST;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int q;
  std::cin >> N >> q;
  for (int i = 1; i <= N; ++i) std::cin >> a[i];
  for (int i = 1; i <= N; ++i) std::cin >> b[i];
  for (int i = 1; i <= N; ++i) pre_c[i] = pre_c[i - 1] + (c[i] = a[i] - b[i]);

  ST.init();

  while (q--) {
    static int l, r;
    static PII res;

    std::cin >> l >> r;

    if (pre_c[r] - pre_c[l - 1] != 0 || (res = ST.qry(l, r)).first > pre_c[l - 1]) {
      std::cout << -1 << '\n';
      continue;
    }

    std::cout << pre_c[l - 1] - res.second << '\n';
  }

  std::cout.flush();
  return 0;
}
