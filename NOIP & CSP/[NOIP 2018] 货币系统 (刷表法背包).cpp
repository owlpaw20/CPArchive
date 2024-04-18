#include <vector>
#include <iostream>
using namespace std;

void solve() {
  int n, mx(0);
  cin >> n;
  vector<int> coin(n);
  vector<int> stat(25001);
  for (int i = 0; i < n; i++) {
    cin >> coin[i];
    stat[coin[i]] = 2;  // 已经存在于面值中 = 2
    mx = max(mx, coin[i]);
  }
  for (int i = 1; i <= mx; i++)
    if (stat[i] != 0)  // 如果该数值可被凑出 != 0
      for (int j = 0; j < n; j++)
        if (i + coin[j] <= mx)
          stat[i + coin[j]] = 1;  // 可以从面值中删除 = 1
  int ans(0);
  for (int st : stat)
    if (st == 2)
      ans++;
  cout << ans << endl;
}

int main() {
  int t;
  cin >> t;
  while (t--) solve();
  return 0;
}
