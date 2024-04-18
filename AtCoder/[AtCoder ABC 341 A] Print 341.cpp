#include <iostream>

#define endl '\n'

using namespace std;

int n;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;

  for (int i = 1; i <= n; i++)
    cout << 10;

  cout << 1 << endl;
  return fflush(stdout), 0;
}
