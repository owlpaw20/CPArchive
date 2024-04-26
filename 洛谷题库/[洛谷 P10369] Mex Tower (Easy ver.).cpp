#include <iostream>

#define endl '\n'

#ifdef _WIN32
#define getchar_unlocked _getchar_nolock
#define putchar_unlocked _putchar_nolock
#endif

namespace FastIO {
  template <typename T>
  T read() {
    T x = 0, f = 1;
    char ch = getchar_unlocked();
    while (ch < '0' || ch > '9') {
      if (ch == '-') f = -f;
      ch = getchar_unlocked();
    }
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - 48, ch = getchar_unlocked();
    return x * f;
  }

  template <typename T>
  void write(T x) {
    if (x < 0) putchar_unlocked('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar_unlocked(x % 10 + '0');
  }
}  // namespace FastIO
using namespace FastIO;

void solve() {
  int n = read<int>();

  for (int i = 1; i <= n; ++i, putchar_unlocked(' '))
    if (i == ((n + 1) >> 1) && (n & 1)) putchar_unlocked('2');
    else if (i <= ((n + 1) >> 1)) putchar_unlocked('0');
    else putchar_unlocked('1');

  putchar_unlocked('\n');
}

int main() {
  int T = read<int>();
  while (T--) solve();
  return fflush(stdout), 0;
}
