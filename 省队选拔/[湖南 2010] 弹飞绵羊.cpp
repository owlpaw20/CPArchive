#include <bits/stdc++.h>

const int MAX_N = 2e5 + 5;
const int MAX_LEN = 5e2;

int N, a[MAX_N];

int len, b_cnt;
int bel[MAX_N];
int l[MAX_LEN], r[MAX_LEN];

int next[MAX_N], step[MAX_N];

void reset_block(int x) {
  for (int i = r[x]; i >= l[x]; --i)
    if (bel[i] != bel[i + a[i]]) step[i] = 1, next[i] = i + a[i];
    else step[i] = step[i + a[i]] + 1, next[i] = next[i + a[i]];
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  len = sqrt(N), b_cnt = N / len + bool(N % len);
  for (int i = 1; i <= N; ++i) std::cin >> a[i], bel[i] = (i - 1) / len + 1;
  for (int i = 1; i <= b_cnt; ++i) l[i] = (i - 1) * len + 1, r[i] = i * len;
  for (int i = b_cnt; i; --i) reset_block(i);

  int M;
  std::cin >> M;

  while (M--) {
    static int type, x, y;
    std::cin >> type >> x;

    ++x;

    if (type == 1) {
      int ans = 0;
      while (x <= N) ans += step[x], x = next[x];
      std::cout << ans << '\n';
    } else {
      std::cin >> y, a[x] = y;
      reset_block(bel[x]);
    }
  }

  std::cout.flush();
  return 0;
}
