#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e5 + 10;

int m, n, h[N], f[N], g[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  while (cin >> m) h[++n] = m;

  // 最长上升子序列
  int ans1 = 0;
  for (int i = 1; i <= n; i++) {
    int l = 1, r = ans1 + 1;
    while (l < r) {
      int mid = (l + r) >> 1;
      if (f[mid] < h[i])
        r = mid;
      else
        l = mid + 1;
    }
    ans1 = max(ans1, l);
    f[l] = h[i];
  }

  cout << ans1 << endl;

  // 最长不增子序列
  int ans2 = 0;
  for (int i = 1; i <= n; i++) {
    int l = 1, r = ans2 + 1;
    while (l < r) {
      int mid = (l + r) >> 1;
      if (g[mid] >= h[i])
        r = mid;
      else
        l = mid + 1;
    }
    ans2 = max(ans2, l);
    g[l] = h[i];
  }

  cout << ans2 << endl;
  return 0;
}
