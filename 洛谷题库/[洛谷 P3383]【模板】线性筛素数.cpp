#include <bitset>
#include <vector>
#include <iostream>

#define endl '\n'

#ifdef _WIN32
#define getchar _getchar_nolock
#define putchar _putchar_nolock
#endif

#ifdef unix
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif

namespace FastIO {
  template <typename T>
  inline T read() {
    T x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
      if (ch == '-') f = -f;
      ch = getchar();
    }
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - 48, ch = getchar();
    return x * f;
  }

  template <typename T>
  inline void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
  }
}  // namespace FastIO
using namespace FastIO;

const int MAX_N = 1e8 + 5;

std::vector<int> primes;
std::bitset<MAX_N> not_prime;

void prep(int n) {
  for (int i = 2; i <= n; ++i) {
    if (!not_prime.test(i)) primes.push_back(i);
    for (int p : primes) {
      if (i * p > n) break;
      not_prime.set(i * p);
      if (i % p == 0) break;
    }
  }
}

int main() {
  int n = read<int>();
  int q = read<int>();

  prep(n);

  while (q--)
    write(primes[read<int>() - 1]), putchar('\n');

  return fflush(stdout), 0;
}
