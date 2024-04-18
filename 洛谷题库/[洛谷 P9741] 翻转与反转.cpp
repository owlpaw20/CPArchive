#include <iostream>
using namespace std;

const int N = 2e6 + 10;

int n;
bool a[N], b[N];

int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  if (n % 2 == 0) {
    int mid = n / 2;
    for (int i = 1; i <= n; i++)
      if (i <= mid)
        b[i] = !a[n - 2 * (i - 1)];
      else
        b[i] = a[2 * (i - mid) - 1];
  } else {
    int mid = n / 2 + 1;
    for (int i = 1; i <= n; i++)
      if (i <= mid)
        b[i] = !a[n - 2 * (i - 1)];
      else
        b[i] = a[2 * (i - mid)];
  }
  for (int i = 1; i <= n; i++)
    cout << b[i] << ' ';
  cout << endl;
  return 0;
}
