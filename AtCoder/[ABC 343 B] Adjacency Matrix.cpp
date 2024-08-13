#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e2 + 5;

int n;
int a[N][N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1, t; j <= n; j++) {
      cin >> t;
      if (t) cout << j << ' ';
    }
    cout << endl;
  }

  return fflush(stdout), 0;
}
