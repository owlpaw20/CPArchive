#include <cstring>
#include <iostream>

#define endl '\n'

const int MAX_N = 5e2 + 5;

int N, M;
int a[MAX_N], b[MAX_N];
int f[MAX_N][MAX_N];

void solve() {
  std::cin >> N;
  for (int i = 1; i <= N; ++i) std::cin >> a[i];
  std::cin >> M;
  for (int i = 1; i <= M; ++i) std::cin >> b[i];

  memset(f, 0, sizeof f);

  /*
      for (int i = 1; i <= N; ++i)
          for (int j = 1; j <= M; ++j)
              if (a[i] != b[j])
                  f[i][j] = f[i - 1][j];
              else {
                  f[i][j] = std::max(f[i][j], 1);
                  for (int k = 1; k < j; ++k)
                      if (a[i] > b[k])
                          f[i][j] = std::max(f[i][j], f[i - 1][k] + 1);
              }
  */

  for (int i = 1; i <= N; ++i) {
    int maxk = 1;
    for (int j = 1; j <= M; ++j)
      if (a[i] == b[j])
        f[i][j] = std::max(f[i][j], maxk);
      else {
        f[i][j] = f[i - 1][j];
        if (a[i] > b[j]) maxk = std::max(maxk, f[i - 1][j] + 1);
      }
  }

  int ans = 0;
  for (int i = 1; i <= M; ++i)
    ans = std::max(ans, f[N][i]);

  std::cout << ans << endl;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) solve();

  return fflush(stdout), 0;
}
