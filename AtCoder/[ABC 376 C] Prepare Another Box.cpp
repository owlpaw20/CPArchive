#include <bits/stdc++.h>

const int MAX_N = 2e5 + 5;

int N, a[MAX_N], b[MAX_N];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  for (int i = 1; i <= N; ++i) std::cin >> a[i];
  for (int i = 1; i < N; ++i) std::cin >> b[i];

  std::sort(a + 1, a + N + 1);
  std::sort(b + 1, b + N);

  int flag = 0;

  for (int i = N, j = N - 1; i && j; --i, --j)
    if (b[j] < a[i]) {
      if (flag) return std::cout << -1 << std::flush, 0;
      flag = a[i], ++j;
    }

  std::cout << (flag ? flag : a[1]) << std::flush;
  return 0;
}
