#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e5 + 10;

int n;
int f[N][3];  // 0 = 未持股且不在冷冻期, 1 = 已持股, 2 = 冷冻期

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  memset(f, 0xCF, sizeof f);
  f[0][0] = 0;

  cin >> n;
  for (int i = 1, a; i <= n; i++) {
    cin >> a;
    f[i][0] = max(f[i - 1][0], f[i - 1][2]);
    f[i][1] = max(f[i - 1][0] - a, f[i - 1][1]);
    f[i][2] = f[i - 1][1] + a;
  }

  cout << max(f[n][0], f[n][2]) << endl;
  fflush(stdout);
  return 0;
}
