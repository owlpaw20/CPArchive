#include <bits/stdc++.h>

using i64 = long long;

const int MAX_N = 1e6 + 5;
const int MAX_LG = 20;

int N, M;
int uni[MAX_LG + 5];
bool ign[MAX_N * MAX_LG], vis[MAX_N];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;

  i64 ans = 0;
  int cnt = 0;

  for (int k = 1; k <= 20; uni[k++] = cnt)
    for (int i = 1; i <= M; ++i)
      if (!ign[k * i])
        ++cnt, ign[k * i] = true;

  for (int i = 2; i <= N; ++i) {
    if (vis[i]) continue;

    int lg = 0;
    for (i64 j = i; j <= N; j *= i) vis[j] = true, ++lg;
    ans += uni[lg];
  }

  std::cout << ans + 1 << std::flush;
  return 0;
}
