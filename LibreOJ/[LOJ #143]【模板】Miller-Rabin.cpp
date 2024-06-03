#include <chrono>
#include <random>
#include <iostream>

using i64 = long long;

const int TESTS = 10;

i64 x;
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

template <typename intT, typename bufT = __int128_t>
intT power(intT b, intT e, intT mod) {
  intT res = 1;
  while (e) ((e & 1) && (res = (bufT)res * b % mod)), b = (bufT)b * b % mod, e >>= 1;
  return res;
}

bool MillerRabin(i64 n) {
  if (n < 2) return false;
  if (n == 2) return true;
  if (!(n & 1)) return false;

  i64 u = n - 1, t = 0;
  while (!(u & 1)) u >>= 1, ++t;

  for (int i = 0; i < TESTS; ++i) {
    i64 a = rnd() % (n - 2) + 2;
    i64 v = power<i64>(a, u, n);
    if (v == 1) continue;

    int s;
    for (s = 0; s < t; ++s) {
      if (v == n - 1) break;
      v = (__int128_t)v * v % n;
    }

    if (s == t) return false;
  }

  return true;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  while (std::cin >> x)
    std::cout.put(MillerRabin(x) ? 'Y' : 'N').put('\n');

  std::cout.flush();
  return 0;
}
