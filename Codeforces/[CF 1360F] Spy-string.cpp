#include <string>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 15;

int n, m;
string s[N];

bool check(string t) {
  for (int i = 2; i <= n; i++) {
    int cnt = 0;
    for (int j = 0; j < m; j++)
      if (s[i][j] != t[j])
        cnt++;
    if (cnt > 1) return false;
  }
  return true;
}

void solve() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    cin >> s[i];

  bool flag = false;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j <= 26; j++) {
      string tmp = s[1];
      tmp[i] = j + 'a';
      if (check(tmp)) {
        flag = true;
        cout << tmp << endl;
        break;
      }
    }
    if (flag) break;
  }

  if (!flag) cout << -1 << endl;
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
