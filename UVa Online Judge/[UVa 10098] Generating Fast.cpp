#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 10;

int T;

void solve() {
  string str;
  cin >> str;
  sort(str.begin(), str.end());
  do {
    cout << str << endl;
  } while (next_permutation(str.begin(), str.end()));
  cout << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> T;
  while (T--) solve();
  return 0;
}
