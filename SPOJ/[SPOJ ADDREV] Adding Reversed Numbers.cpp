#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

int n;

void solve() {
  string s1, s2;
  cin >> s1 >> s2;
  reverse(s1.begin(), s1.end());
  reverse(s2.begin(), s2.end());
  int ans = stoi(s1) + stoi(s2);
  string s;
  while (ans) {
    s += (char)(ans % 10 + '0');
    ans /= 10;
  }
  while (s.front() == '0' && s.size() > 1) s.erase(0, 1);
  cout << s << endl;
}

int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  cin >> n;
  while (n--) solve();
  return 0;
}
