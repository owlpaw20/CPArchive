#include <cmath>
#include <climits>
#include <iostream>
#include <unordered_map>
#define INF INT_MAX
using namespace std;
using MII = unordered_map<int, int>;
using PII = pair<int, int>;

int n, m1, m2, ans = INF;

MII get_divisors(int x) {
  MII ret;
  int lmt = sqrt(x);
  for (int i = 2; i <= lmt; i++)
    if (x % i == 0) {
      int cnt = 0;
      while (x % i == 0)
        x /= i, cnt++;
      ret[i] = cnt;
    }
  if (x > 1) ret[x] = 1;
  return ret;
}

int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  cin >> n >> m1 >> m2;
  MII m1d = get_divisors(m1);
  while (n--) {
    int s, t = 0;
    cin >> s;
    MII sd = get_divisors(s);
    for (PII p : m1d) {
      int k = p.first, v = p.second;
      if (!sd.count(k)) {
        t = INF;
        break;
      } else
        t = max(t, (v * m2 + sd[k] - 1) / sd[k]);
    }
    ans = min(ans, t);
  }
  if (ans == INF)
    return (cout << -1 << endl && 0);
  cout << ans << endl;
  return 0;
}
