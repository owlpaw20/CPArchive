#include <bits/stdc++.h>

const int MAX_N = 4e3 + 5;

int N, a, b, c;
int f[MAX_N];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> a >> b >> c;
  memset(f + 1, -1, sizeof(int) * N);

  auto upd = [&](int x) {
    for (int i = x; i <= N; ++i)
      if (f[i - x] != -1)
        f[i] = std::max(f[i], f[i - x] + 1);
  };

  upd(a), upd(b), upd(c);

  std::cout << f[N] << std::flush;
  return 0;
}
