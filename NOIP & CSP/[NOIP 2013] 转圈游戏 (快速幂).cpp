#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;

int fast_exp(int a, int b, int p) {
  int ret = 1;
  while (b) {
    if (b & 1) ret = (i64)ret * a % p;
    a = (i64)a * a % p;
    b >>= 1;
  }
  return ret;
}

int n, m, K, x;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m >> K >> x;
  cout << (x + (i64)fast_exp(10, K, n) * m % n) % n << endl;
  fflush(stdout);
  return 0;
}
