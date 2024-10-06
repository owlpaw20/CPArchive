#include <bits/stdc++.h>

namespace FastIO {
  template <typename T>
  T read() {
    short int f = 1;
    T var = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
      if (ch == '-') f = -f;
      ch = getchar();
    }
    while (ch >= '0' && ch <= '9') var = var * 10 + ch - '0', ch = getchar();
    return var * f;
  }

  template <typename T>
  void write(T x) {
    static short int stack[10];
    if (x < 0) putchar('-'), x = -x;
    int top = 0;
    do stack[top++] = x % 10, x /= 10;
    while (x);
    while (top) putchar(stack[--top] + 48);
  }
}  // namespace FastIO
using namespace FastIO;

int main() {
  int N = read<int>();
  int occupy = 0, cnt = 0;

  for (int i = 1, x; i <= N; ++i) {
    x = read<int>();
    if (!cnt) occupy = x, cnt = 1;
    else occupy == x ? ++cnt : --cnt;
  }

  write(occupy);
  return 0;
}
