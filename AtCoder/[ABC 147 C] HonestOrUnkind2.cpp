#include <bits/stdc++.h>

using PII = std::pair<int, int>;

const int MAX_N = 20;

int N, a[MAX_N];
PII b[MAX_N][MAX_N];
int type[MAX_N];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;

  for (int i = 1; i <= N; ++i) {
    std::cin >> a[i];
    for (int j = 1; j <= a[i]; ++j) {
      std::cin >> b[i][j].first >> b[i][j].second;
      b[i][j].second = (b[i][j].second == 0) ? -1 : 1;
    }
  }

  int ans = 0;

  for (int st = 0; st < (1 << N); ++st) {
    memset(type, 0, sizeof(int) * (N + 1));

    for (int i = 1; i <= N; ++i)
      if ((st >> (i - 1)) & 1)
        type[i] = 1;

    bool valid = true;
    bool flag = true;

    while (valid && flag) {
      flag = false;
      for (int i = 1; i <= N; ++i) {
        if (type[i] == 1)
          for (int j = 1; j <= a[i]; ++j) {
            if (type[b[i][j].first]) {
              if (type[b[i][j].first] != b[i][j].second) {
                valid = false;
                break;
              }
            } else {
              type[b[i][j].first] = b[i][j].second;
              flag = true;
            }
          }
      }
    }

    if (valid) ans = std::max(ans, __builtin_popcount(st));
  }

  std::cout << ans << std::endl;
  return 0;
}
