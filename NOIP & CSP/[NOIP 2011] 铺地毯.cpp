#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e4 + 10;

int n, ex, ey;
int x[N], y[N], lx[N], ly[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> x[i] >> y[i] >> lx[i] >> ly[i];

  cin >> ex >> ey;

  int ans = -1;
  for (int i = 1; i <= n; i++)
    if (x[i] <= ex && ex <= x[i] + lx[i] &&
        y[i] <= ey && ey <= y[i] + ly[i])
      ans = i;

  cout << ans << endl;
  fflush(stdout);
  return 0;
}
