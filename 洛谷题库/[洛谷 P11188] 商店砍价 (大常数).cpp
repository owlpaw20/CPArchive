#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned int;
using PBV = std::pair<bool, std::vector<int>>;

const int MAX_V = 10;

int N, v[MAX_V];

void solve() {
  std::string s;
  std::vector<std::vector<int>> pos(MAX_V);

  std::cin >> s, N = s.length();
  for (int i = 1; i <= 9; ++i) std::cin >> v[i];

  if (N <= 20) {
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

  auto check = [&](int num) -> PBV {
    std::vector<int> excerpt;
    int prev_pos = -1;

    while (num) {
      excerpt.push_back(num % 10), num /= 10;
      if (!excerpt.back()) return {false, std::vector<int>()};
    }

    for (int x : excerpt) {
      auto it = std::upper_bound(pos[x].begin(), pos[x].end(), prev_pos);
      if (it == pos[x].end()) return {false, std::vector<int>()};
      prev_pos = *it;
    }

    return {true, excerpt};
  };

  i64 ans = std::numeric_limits<i64>::max();

  for (int num = 11111; num <= 99999; ++num) {
    auto [flag, excerpt] = check(num);
    if (!flag) continue;

    std::vector<int> del_cnt(MAX_V);
    for (int i = 1; i <= 9; ++i) del_cnt[i] = pos[i].size();
    for (int x : excerpt) --del_cnt[x];

    i64 pre_cost = 0;
    for (int i = 1; i <= 9; ++i) pre_cost += (i64)del_cnt[i] * v[i];

    for (u32 S = 0; S < (1 << 5); ++S) {
      i64 clear_cost = 0, del_cost = 0;
      for (int i = 0; i < 5; ++i)
        if (S >> i & 1) (clear_cost *= 10) += excerpt[i];
        else del_cost += v[excerpt[i]];
      ans = std::min(ans, pre_cost + clear_cost + del_cost);
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
