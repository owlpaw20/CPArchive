#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned int;

const int MAX_V = 10;

int N, v[MAX_V];

void solve() {
  std::string s;
  std::vector<std::vector<int>> pos(MAX_V);

  std::cin >> s, N = s.length();
  for (int i = 1; i <= 9; ++i) std::cin >> v[i];

  if (N <= 5) {
    i64 ans = std::numeric_limits<i64>::max();

    for (u32 S = 0; S < (1U << N); ++S) {
      i64 clear_cost = 0, del_cost = 0;
      for (int i = 0; i < N; ++i)
        if (S >> i & 1) (clear_cost *= 10) += s[i] - '0';
        else del_cost += v[s[i] - '0'];
      ans = std::min(ans, clear_cost + del_cost);
    }

    std::cout << ans << '\n';
    return;
  }

  for (int i = 0; i < N; ++i) pos[s[i] - '0'].push_back(i);

  auto check = [&](int a, int b, int c, int d, int e) -> bool {
    auto it = std::upper_bound(pos[a].begin(), pos[a].end(), -1);
    if (it == pos[a].end()) return false;

    it = std::upper_bound(pos[b].begin(), pos[b].end(), *it);
    if (it == pos[b].end()) return false;

    it = std::upper_bound(pos[c].begin(), pos[c].end(), *it);
    if (it == pos[c].end()) return false;

    it = std::upper_bound(pos[d].begin(), pos[d].end(), *it);
    if (it == pos[d].end()) return false;

    it = std::upper_bound(pos[e].begin(), pos[e].end(), *it);
    if (it == pos[e].end()) return false;

    return true;
  };

  i64 ans = std::numeric_limits<i64>::max();

  for (int a = 1; a <= 9; ++a)
    for (int b = 1; b <= 9; ++b)
      for (int c = 1; c <= 9; ++c)
        for (int d = 1; d <= 9; ++d)
          for (int e = 1; e <= 9; ++e)
            if (check(a, b, c, d, e)) {
              std::vector<int> del_cnt(MAX_V);
              for (int i = 1; i <= 9; ++i) del_cnt[i] = pos[i].size();
              --del_cnt[a], --del_cnt[b], --del_cnt[c], --del_cnt[d], --del_cnt[e];

              i64 cost = 0;
              for (int i = 1; i <= 9; ++i) cost += (i64)del_cnt[i] * v[i];

              for (u32 S = 0; S < (1U << 5); ++S) {
                i64 clear_cost = 0, del_cost = 0;
                S >> 0 & 1 ? (clear_cost *= 10) += a : del_cost += v[a];
                S >> 1 & 1 ? (clear_cost *= 10) += b : del_cost += v[b];
                S >> 2 & 1 ? (clear_cost *= 10) += c : del_cost += v[c];
                S >> 3 & 1 ? (clear_cost *= 10) += d : del_cost += v[d];
                S >> 4 & 1 ? (clear_cost *= 10) += e : del_cost += v[e];
                ans = std::min(ans, cost + clear_cost + del_cost);
              }
            }

  std::cout << ans << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T >> T;
  while (T--) solve();

  std::cout.flush();
  return 0;
}
