#include <iostream>

using namespace std;
using i64 = long long;

const int N = 1e5 + 10;
const int M = 1e6 + 10;

int n, a[N];
int vis[M];
i64 ans[M];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> a[i], vis[a[i]]++;

  for (int i = 1; i <= 1e6; i++)
    if (vis[i])
      for (int j = 1; i * j <= 1e6; j++)
        ans[i * j] += vis[i];

  for (int i = 1; i <= n; i++)
    cout << ans[a[i]] - 1 << endl;
  return 0;
}
