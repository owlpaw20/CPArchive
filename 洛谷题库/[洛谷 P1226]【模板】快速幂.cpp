#include <cstdio>
#include <iostream>
using namespace std;

long long a, b, p;

int qpow(long long a, long long b) {
  long long res = 1;
  if (b == 0) return 1;
  while (b) {
    if (b & 1) res = (long long)res * a % p;
    a = (long long)a * a % p;
    b >>= 1;
  }
  return res;
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> a >> b >> p;
  printf("%lld^%lld mod %lld=%lld\n", a, b, p, qpow(a, b) % p);
  return 0;
}
