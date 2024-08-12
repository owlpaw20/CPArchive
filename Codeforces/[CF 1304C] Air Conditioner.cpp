#include <bits/stdc++.h>

const int MAX_N = 1e2 + 5;

int N, m;

struct Customer {
  int l, r, t;
} a[MAX_N];

void solve() {
  std::cin >> N >> m;

  bool flag = true;
  int L = m, R = m;

  for (int i = 1, l, r, t; i <= N; ++i) {
    std::cin >> t >> l >> r;
    a[i] = {l, r, t};

    if (flag) {
      int d = (i == 1) ? t : (t - a[i - 1].t);
      L = std::max(L - d, l);
      R = std::min(R + d, r);
      flag &= L <= R;
    }
  }

  if (flag) puts("YES");
  else puts("NO");
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) solve();

  return 0;
}
