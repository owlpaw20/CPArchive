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
}  // namespace FastIO
using namespace FastIO;

void solve() {
  int n = read<int>();
  int mid_1[3] = {-1, -1, -1};
  int mid_2[3] = {-1, -1, -1};

  if (n == 1) {
    int x = read<int>();
    std::cout << ((x == 2) ? "No" : "Yes") << endl;
    return;
  }

  if (n == 2) {
    int x = read<int>();
    int y = read<int>();
    std::cout << (((x == 1 && y == 0) || (x == 0 && y == 1)) ? "Yes" : "No") << endl;
    return;
  }

  if (n == 3) {
    int x = read<int>();
    int y = read<int>();
    int z = read<int>();
    std::cout << (((x > 0 && y >= 2 && z == 0) || (x == 0 && y >= 2 && z > 0)) ? "Yes" : "No") << endl;
    return;
  }

  for (int i = 1, t1 = 0, t2 = 0, p; i <= n; ++i) {
    p = read<int>();
    if (t1 < 3 && i > (n >> 1) - 1) mid_1[t1++] = p;
    if (t2 < 3 && i > (n >> 1) - 2) mid_2[t2++] = p;
  }

  bool flag = false;

  if (n & 1) {
    if ((mid_1[0] > 0 && mid_1[1] >= 2 && mid_1[2] == 0) ||
        (mid_1[0] == 0 && mid_1[1] >= 2 && mid_1[2] > 0)) flag = true;
  } else if ((mid_1[0] == 0 && mid_1[1] == 1 && mid_1[2] > 0) ||
             (mid_2[0] > 0 && mid_2[1] == 1 && mid_2[2] == 0)) flag = true;

  std::cout << (flag ? "Yes" : "No") << endl;
}

int main() {
  int T = read<int>();
  while (T--) solve();
  return fflush(stdout), 0;
}
