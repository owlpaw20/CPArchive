#include <iostream>
#include <string>

using u64 = unsigned long long;

const int MAX_N = 20;

int N;
std::string s;
u64 f[MAX_N << 1][MAX_N], p10[MAX_N];
std::string g[MAX_N << 1][MAX_N];

void prep() {
  p10[0] = 1;
  for (int i = 1; i <= 18; ++i) p10[i] = p10[i - 1] * 10;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> s;
  prep(), s = '\0' + s;

  for (int i = 1; i <= N + N; ++i)
    for (int j = 0; j <= i && j <= N; ++j) {
      int digit = s[i] - '0';
      bool flag = true;

      if (j > 0)
        if (u64 sum = f[i - 1][j - 1] + p10[N - j] * digit; flag || sum > f[i][j])
          f[i][j] = sum, g[i][j] = g[i - 1][j - 1] + 'H', flag = false;

      if (i - j > 0 && i - j <= N)
        if (u64 sum = f[i - 1][j] + p10[N - i + j] * digit; flag || sum > f[i][j])
          f[i][j] = sum, g[i][j] = g[i - 1][j] + 'M', flag = false;
    }

  std::cout << g[N + N][N] << '\n';
  return 0;
}
