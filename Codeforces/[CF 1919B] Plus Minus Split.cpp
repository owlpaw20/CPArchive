#include <stack>
#include <iostream>

#define endl '\n'

using namespace std;

void solve() {
  int n;
  stack<char> stk;

  cin >> n;

  for (int i = 1; i <= n; i++) {
    char ch;
    cin >> ch;
    if (!stk.empty() && ch != stk.top())
      stk.pop();
    else
      stk.emplace(ch);
  }

  int ans = 0;
  while (!stk.empty()) {
    stk.pop();
    ans++;
  }

  cout << ans << endl;
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
