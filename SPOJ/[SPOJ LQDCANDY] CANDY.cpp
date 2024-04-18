#include <cmath>
#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;

int T;

i64 power(i64 b, int e) {
  i64 ret = 1;
  while (e) {
    if (e & 1) ret = ret * b;
    b = b * b;
    e >>= 1;
  }
  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> T;
  while (T--) {
    i64 n;
    cin >> n;
    i64 ans = 1LL << (int)ceil(log2(n));
    cout << ans << ' ';
    while (n % 2 == 0)
      n >>= 1, ans >>= 1;
    cout << log2(ans) << endl;
  }

  fflush(stdout);
  return 0;
}
