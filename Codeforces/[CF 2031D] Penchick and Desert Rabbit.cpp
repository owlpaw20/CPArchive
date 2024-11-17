#include <bits/stdc++.h>

const int MAX_N = 5e5 + 5;

int N, ans[MAX_N];
int a[MAX_N], pre[MAX_N], suf[MAX_N];

void solve() {
  std::cin >> N;

  pre[0] = 0;
  suf[N + 1] = std::numeric_limits<int>::max();

  for (int i = 1; i <= N; ++i) {
    std::cin >> a[i];
    pre[i] = std::max(pre[i - 1], a[i]);
  }

  for (int i = N; i >= 1; --i) {
    suf[i] = std::min(suf[i + 1], a[i]);
    ans[i] = pre[i] > suf[i + 1] ? ans[i + 1] : pre[i];
  }

  for (int i = 1; i <= N; ++i) std::cout << ans[i] << ' ';
  std::cout.put('\n');
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) solve();

  return 0;
}
