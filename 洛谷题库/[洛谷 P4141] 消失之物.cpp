#include <iostream>

const int MAX_N = 2e3 + 5;
const int MOD = 10;

int N, M;
int w[MAX_N];
int f[MAX_N], g[MAX_N];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;
  for (int i = 1; i <= N; ++i) std::cin >> w[i];

  f[0] = 1;

  for (int i = 1; i <= N; ++i)
    for (int j = M; j >= w[i]; --j)
      f[j] = (f[j] + f[j - w[i]]) % 10;

  for (int i = 1; i <= N; ++i) {
    g[0] = 1;
    for (int j = 1; j <= M; ++j) {
      if (w[i] > j) g[j] = f[j] % 10;
      else g[j] = (f[j] - g[j - w[i]] + 10) % 10;
      std::cout << g[j];
    }
    std::cout << '\n';
  }

  std::cout.flush();
  return 0;
}
