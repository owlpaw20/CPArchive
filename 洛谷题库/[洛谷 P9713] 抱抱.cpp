#include <iostream>
using namespace std;
using lng = unsigned long long;

lng a, b, c, m;

int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  cin >> a >> b >> c >> m;
  lng vol = a * b * c;
  lng x = 0, y = 0, z = 0;
  while (m--) {
    int opt, k;
    cin >> opt >> k;
    if (opt == 1 && k >= x) {
      vol -= (k - x) * (b - y) * (c - z);
      x = k;
    } else if (opt == 2 && k >= y) {
      vol -= (a - x) * (k - y) * (c - z);
      y = k;
    } else if (opt == 3 && k >= z) {
      if (k < z) continue;
      vol -= (a - x) * (b - y) * (k - z);
      z = k;
    }
    cout << vol << endl;
  }
  return 0;
}
