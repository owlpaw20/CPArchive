#include <vector>
#include <iostream>
using namespace std;
using i64 = long long;

int n, m, q, k;

int main() {
  cin >> n >> m >> q >> k;
  vector<int> r(n + 1), c(m + 1);
  while (q--) {
    int o, x;
    cin >> o >> x;
    if (o & 1)
      r[x] = (r[x] + 1) % k;
    else
      c[x] = (c[x] + 1) % k;
  }
  i64 a(0), b(0);
  vector<i64> rr(k + 1), cc(k + 1);
  for (int i = 1; i <= n; i++)
    if (r[i] > 0)
      a++, rr[r[i]]++;
  for (int i = 1; i <= m; i++)
    if (c[i] > 0)
      b++, cc[c[i]]++;
  i64 ans(a * m + b * n - a * b);
  for (int i = 1; i <= k - 1; i++)
    ans -= rr[i] * cc[k - i];
  cout << ans << endl;
  return 0;
}
