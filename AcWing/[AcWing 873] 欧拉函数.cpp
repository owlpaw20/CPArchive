#include <cmath>
#include <iostream>
using namespace std;

int n;

int phi(int x) {
  int ret = x, lmt = sqrt(x);
  for (int i = 2; i <= lmt; i++)
    if (x % i == 0) {
      ret = ret / i * (i - 1);
      while (x % i == 0) x /= i;
    }
  if (x != 1) ret = ret / x * (x - 1);
  return ret;
}

int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  cin >> n;
  while (n--) {
    int a;
    cin >> a;
    cout << phi(a) << endl;
  }
  return 0;
}
