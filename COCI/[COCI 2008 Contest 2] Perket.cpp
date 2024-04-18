#include <climits>
#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;

int n;
int s[15], b[15];
int ans = INT_MAX;

void dfs(int x, int sour, int bitter) {
  if (x > n) {
    if (sour == 1 && bitter == 0) return;
    ans = min(abs(sour - bitter), ans);
    return;
  }

  dfs(x + 1, sour * s[x], bitter + b[x]);
  dfs(x + 1, sour, bitter);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> s[i] >> b[i];

  dfs(1, 1, 0);

  cout << ans << endl;
  fflush(stdout);
  return 0;
}
