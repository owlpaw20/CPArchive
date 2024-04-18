#include <iostream>
using namespace std;
using i64 = long long;

const int N = 1e5 + 10;

i64 n, a[N], ans, cnt;

int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    a[i] += a[i - 1];
  }
  if (a[n] % 3) return (cout << 0 << endl) && 0;
  i64 part = a[n] / 3;
  for (int i = 1; i < n; i++) {
    if (a[i] == 2 * part) ans += cnt;
    if (a[i] == part) cnt++;
  }
  cout << ans << endl;
  return 0;
}
