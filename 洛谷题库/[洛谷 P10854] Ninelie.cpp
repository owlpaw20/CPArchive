#include <bits/stdc++.h>

const int MAX_N = 2e3 + 5;

int N, R;
bool a[MAX_N];
std::vector<int> ans;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> R;

  for (int i = 1; i <= N; ++i) {
    std::cin >> a[i];
    a[i - 1] ^= a[i];
  }

  for (int i = 1; i <= ((N - 1) >> 1); ++i)
    if (a[i])
      for (int j = i; j; --j)
        ans.push_back(j);

  for (int i = N - 1; i > ((N - 1) >> 1); --i)
    if (a[i])
      for (int j = i + 1; j <= N; ++j)
        ans.push_back(j);

  std::cout << ans.size() << '\n';
  for (int x : ans) std::cout << x << ' ';

  std::cout.flush();
  return 0;
}
