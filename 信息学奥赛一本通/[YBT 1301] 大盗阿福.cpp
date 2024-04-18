#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e5 + 5;

int f[N];

void solve() {
  int n;
  cin >> n >> f[1];

  for (int i = 2, a; i <= n; i++)
    cin >> a, f[i] = max(f[i - 1], f[i - 2] + a);

  cout << f[n] << endl;
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
