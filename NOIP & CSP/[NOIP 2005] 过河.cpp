#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e2 + 10;
const int M = 1e4 + 10;
const int P = 1e5 + 10;
const int INF = 0x3F3F3F3F;

int L, S, T, m;
int stone[N], f[M];
bool flag[P];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  memset(f, 0x3F, sizeof f);

  stone[0] = f[0] = 0;

  cin >> L >> S >> T >> m;
  for (int i = 1; i <= m; i++) cin >> stone[i];
  sort(stone, stone + m + 2);

  int idx = 0;
  for (int i = 1; i <= m + 1; i++) {
    if (stone[i] - stone[i - 1] <= T)
      idx += stone[i] - stone[i - 1];
    else
      idx += (stone[i] - stone[i - 1]) % T + T;
    flag[idx] = true;
  }

  for (int i = 1; i <= idx + T; i++)
    for (int j = S; j <= T; j++)
      if (i - j >= 0)
        f[i] = min(f[i], f[i - j] + flag[i]);

  int ans = INF;
  for (int i = idx; i <= idx + T; i++)
    ans = min(ans, f[i]);

  cout << ans << endl;
  return 0;
}
