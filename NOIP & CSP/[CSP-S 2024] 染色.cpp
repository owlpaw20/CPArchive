#include <bits/stdc++.h>

using i64 = long long;

const int MAX_N = 2e5 + 5;
const int MAX_V = 1e6 + 5;

int N, a[MAX_N], prev[MAX_V];
i64 f[MAX_N], sum[MAX_N];

void solve() {
  std::cin >> N;
  memset(prev, 0, sizeof prev);

  for (int i = 1; i <= N; ++i) {
    std::cin >> a[i];
    // 对于极长同值段，其内部能产生的贡献是一定的，可以预处理
    sum[i] = sum[i - 1] + a[i] * (a[i] == a[i - 1]);
  }

  for (int i = 1; i <= N; ++i) {
    f[i] = f[i - 1];

    // 如果之前存在同色同值数，则加入转移过来的贡献：
    // 首先是同色同值带来的贡献 a[i]
    // 接着是预处理出的 (prev[a[i]] + 1, i) 内的所有贡献即 sum[i] - sum[prev[a[i]] + 1]
    // 还要加上中间夹着的这一段的首位置 prev[a[i]] + 1 可能存在的贡献 f[prev[a[i]] + 1]

    if (prev[a[i]]) f[i] = std::max(f[i], a[i] + f[prev[a[i]] + 1] + sum[i] - sum[prev[a[i]] + 1]);
    prev[a[i]] = i;
  }

  std::cout << f[N] << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) solve();

  std::cout.flush();
  return 0;
}
