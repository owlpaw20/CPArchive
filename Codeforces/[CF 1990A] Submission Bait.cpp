#include <cstring>
#include <iostream>

constexpr int MAX_N = 55;

int cnt[MAX_N];

bool solve() {
  int N;
  std::cin >> N;
  memset(cnt, 0, sizeof(int) * (N + 1));

  for (int i = 1, x; i <= N; ++i) std::cin >> x, ++cnt[x];

  for (int i = 1; i <= N; ++i)
    if (cnt[i] % 2)
      return true;

  return false;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) puts(solve() ? "Yes" : "No");

  return 0;
}
