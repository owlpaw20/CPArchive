#include <iostream>

using LL = long long;

const int MAX_N = 1e2 + 5;

int N, M, s[MAX_N];
int c[MAX_N][MAX_N];

template <typename intT, typename bufT = LL>
intT power(intT b, intT e, intT mod) {
  intT res = 1;
  for (; e; e >>= 1)
    ((e & 1) && (res = (bufT)res * b % mod)), b = (bufT)b * b % mod;
  return res;
}

int mod(LL x) { return ((x % M) + M) % M; }

int GaussJordan() {
  int rank = 0;

  for (int row = 1, col = 1, max_r; col <= N; ++col) {
    max_r = row;
    for (int i = row; i <= N; ++i)
      if (c[i][col] > c[max_r][col])
        max_r = i;

    if (!c[max_r][col]) continue;
    for (int i = col; i <= N + 1; ++i) std::swap(c[max_r][i], c[row][i]);

    int fm = power(c[row][col], M - 2, M);
    for (int i = N + 1; i >= col; --i)
      c[row][i] = mod((LL)c[row][i] * fm);

    for (int i = row + 1; i <= N; ++i)
      if (c[i][col])
        for (int j = N + 1; j >= col; --j)
          c[i][j] = mod(c[i][j] - (LL)c[row][j] * c[i][col]);

    ++row, ++rank;
  }

  if (rank < N) {
    for (int i = rank + 1; i <= N; ++i)
      for (int j = 1; j <= N + 1; ++j)
        if (c[i][j])
          return -1;
    return 0;
  }

  for (int i = N; i; --i)
    for (int j = i + 1; j <= N; ++j)
      c[i][N + 1] = mod(c[i][N + 1] - (LL)c[i][j] * c[j][N + 1]);

  return 1;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;

  for (int i = 1, k, t; i <= N; ++i) {
    std::cin >> k;
    c[i][i] = 1;
    while (k--) std::cin >> t, c[t][i] = 1;
  }

  for (int i = 1; i <= N; ++i) std::cin >> s[i];
  for (int i = 1; i <= N; ++i) {
    std::cin >> c[i][N + 1];
    c[i][N + 1] = mod(c[i][N + 1] - s[i]);
  }

  int res = GaussJordan();

  if (res != -1)
    for (int i = 1; i <= N; ++i)
      std::cout << mod(c[i][N + 1]) << ' ';
  else
    std::cout << "niuza";

  std::cout << std::endl;
  return 0;
}
