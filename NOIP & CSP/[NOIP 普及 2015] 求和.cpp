#include <vector>
#include <iostream>
using namespace std;

const int MOD = 1e4 + 7;

int n, m;

int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  cin >> n >> m;
  vector<int> v(n + 1);
  vector<int> c(n + 1);
  for (int i = 1; i <= n; i++) cin >> v[i];
  for (int i = 1; i <= n; i++) cin >> c[i];
  vector<vector<int>> sum(n + 1, vector<int>(2));
  vector<vector<int>> cnt(n + 1, vector<int>(2));
  for (int i = 1; i <= n; i++) {
    sum[c[i]][i % 2] = (sum[c[i]][i % 2] + v[i]) % MOD;
    cnt[c[i]][i % 2] += 1;
  }
  int ans(0);
  for (int i = 1; i <= n; i++)
    ans = (ans + i * ((cnt[c[i]][i % 2] - 2) * v[i] % MOD + sum[c[i]][i % 2]) % MOD) % MOD;
  cout << ans << endl;
  return 0;
}
