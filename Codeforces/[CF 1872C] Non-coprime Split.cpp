#include <cmath>
#include <iostream>
using namespace std;

int T;

void solve() {
  int l, r;
  cin >> l >> r;
  int lmt = sqrt(r);
  for (int i = 2; i <= lmt; i++) {
    int t = r / i;
    t *= i;
    if (t < l) continue;
    if (min(i, t - i) == 1) continue;
    cout << i << " " << t - i << endl;
    return;
  }
  cout << -1 << endl;
}

int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  cin >> T;
  while (T--) solve();
  return 0;
}
