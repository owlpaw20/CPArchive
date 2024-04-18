#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e5 + 5;

int a[N];
int p[N];

void solve() {
  int n, x;
  cin >> n >> x;

  bool flag = false;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    p[i] = p[i - 1] + a[i];
    flag |= a[i] % x;
  }

  if (!flag)
    cout << -1 << endl;
  else if (p[n] % x)
    cout << n << endl;
  else {
    int r = 1;
    while (p[r] % x == 0) r++;
    int from_start = r;

    int l = n;
    while ((p[n] - p[l - 1]) % x == 0) l--;
    int from_end = n - l + 1;

    cout << n - min(from_start, from_end) << endl;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while (T--) solve();

  fflush(stdout);
  return 0;
}
