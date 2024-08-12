#include <bits/stdc++.h>

using PII = std::pair<int, int>;

const int MAX_N = 2e3 + 5;

int N, M;
char mp[MAX_N][MAX_N];

std::string ans;
std::set<PII> cand;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;

  for (int i = 1; i <= N; ++i)
    for (int j = 1; j <= M; ++j)
      std::cin >> mp[i][j];

  cand.emplace(1, 1);

  for (int step = 1; step < N + M; ++step) {
    auto [x, y] = *cand.begin();
    ans += mp[x][y];

    char next_c = 127;
    std::set<PII> next;

    for (auto [tx, ty] : cand) {
      if (tx < N) next_c = std::min(next_c, mp[tx + 1][ty]);
      if (ty < M) next_c = std::min(next_c, mp[tx][ty + 1]);
    }

    for (auto [tx, ty] : cand) {
      if (tx < N && mp[tx + 1][ty] == next_c) next.emplace(tx + 1, ty);
      if (ty < M && mp[tx][ty + 1] == next_c) next.emplace(tx, ty + 1);
    }

    cand = next;
  }

  std::cout << ans << std::flush;
  return 0;
}
