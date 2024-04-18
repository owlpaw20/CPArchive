#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;
using PII = pair<int, int>;

const int N = 5e3 + 10;

int n;
int f[N];
PII a[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> a[i].first >> a[i].second;

  sort(a + 1, a + n + 1);

  int ans = 0;
  for (int i = 1; i <= n; i++) {
    f[i] = 1;
    for (int j = 1; j < i; j++)
      if (a[j].second < a[i].second)
        f[i] = max(f[i], f[j] + 1);
    ans = max(ans, f[i]);
  }

  cout << ans << endl;
  fflush(stdout);
  return 0;
}
