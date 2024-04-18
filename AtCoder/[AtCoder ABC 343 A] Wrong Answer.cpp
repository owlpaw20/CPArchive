#include <iostream>

#define endl '\n'

using namespace std;

int a, b;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> a >> b;

  int ans = 0;
  while (a + b == ans) ans++;

  cout << ans << endl;
  return fflush(stdout), 0;
}
