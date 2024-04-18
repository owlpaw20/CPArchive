#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1e2 + 10;
const int M = 2.5e4 + 10;

int T;
bool f[M];
int coin[N];

void solve() {
  memset(f, false, sizeof f);
  memset(coin, 0, sizeof coin);
  int n, ans = 0;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> coin[i];
  sort(coin + 1, coin + n + 1);

  f[0] = true;  // 0 肯定可以表示出来
  for (int i = 1; i <= n; i++) {
    if (f[coin[i]] == true) continue;  // 如果已可以表示则删除
    ans += 1;                          // 如果尚不能表示就增加
    for (int j = coin[i]; j <= coin[n]; j++)
      f[j] = (f[j] || f[j - coin[i]]);  // 能表示的都表示出来
  }
  cout << ans << endl;
}

int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  cin >> T;
  while (T--) solve();
  return 0;
}
