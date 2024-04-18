#include <iostream>

#define endl '\n'

using namespace std;

const int N = 4e6 + 10;
const int INF = 0x7FFFFFFF;

int n, m, maxt = -1;
int cnt[N], sum[N], f[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    int t;
    cin >> t;
    maxt = max(maxt, t);
    cnt[t]++;
    sum[t] += t;
  }

  for (int i = 1; i < maxt + m; i++) {
    cnt[i] += cnt[i - 1];
    sum[i] += sum[i - 1];
  }

  for (int i = 0; i < maxt + m; i++) {
    if (i >= m && cnt[i - m] == cnt[i]) {
      f[i] = f[i - m];
      continue;
    }
    f[i] = cnt[i] * i - sum[i];
    for (int j = max(i - m - m + 1, 0); j <= i - m; j++)
      f[i] = min(f[i], f[j] + (cnt[i] - cnt[j]) * i - (sum[i] - sum[j]));
  }

  int ans = INF;
  for (int i = maxt; i < maxt + m; i++)
    ans = min(ans, f[i]);

  cout << ans << endl;
  fflush(stdout);
  return 0;
}
