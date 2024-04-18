#include <set>
#include <iostream>
#include <algorithm>
using namespace std;
using PII = pair<int, int>;

const int N = 1e4 + 10;

int n, p, h, q;
int d[N];
set<PII> s;

int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  cin >> n >> p >> h >> q;
  while (q--) {
    int a, b;
    cin >> a >> b;
    if (a > b) swap(a, b);
    if (!s.insert({a, b}).second) continue;
    d[a + 1] -= 1;
    d[b] += 1;
  }
  for (int i = 1; i <= n; i++) {
    d[i] += d[i - 1];
    cout << d[i] + h << endl;
  }
  return 0;
}
