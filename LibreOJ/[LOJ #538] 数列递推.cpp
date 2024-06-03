#include <iostream>

namespace FastIO {
  const int MAX_BUF = 1 << 16;
  char buf[MAX_BUF], *p1, *p2;
  char pbuf[MAX_BUF], *pp = pbuf;

  char getchar() { return (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAX_BUF, stdin), p1 == p2) ? EOF : *p1++); }
  void putchar(char c) { (((pp - pbuf == MAX_BUF) && (fwrite(pbuf, 1, MAX_BUF, stdout), pp = pbuf)), *pp++ = c); }
  void flush() { (pp - pbuf) && fwrite(pbuf, 1, pp - pbuf, stdout); }

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
    static int stack[40];
    if (x < 0) putchar('-'), x = -x;
    int top = 0;
    do stack[top++] = x % 10, x /= 10;
    while (x);
    while (top) putchar(stack[--top] + 48);
  }

  template <typename T>
  void write(T x, char c) { write(x), putchar(c); }
}  // namespace FastIO
using namespace FastIO;

using f128 = long double;

const int MAX_N = 1e5 + 5;
const int LIMIT = 40;

int N, Q;
int s[MAX_N], max_S = -1;
f128 a[MAX_N];

int main() {
  N = read<int>();
  for (int i = 1; i <= N; i++) s[i] = read<int>();
  for (int i = 1; i <= N; i++)
    if (s[i] > LIMIT) {
      max_S = s[N];
      N = i - 1;
      break;
    }

  Q = read<int>();

  while (Q--) {
    a[0] = read<int>(), a[1] = read<int>();
    int K = read<int>();

    if (!a[0] && !a[1]) {
      write(s[1], ' '), write(s[1], '\n');
      continue;
    }

    for (int j = 2; j <= LIMIT; j++) a[j] = a[j - 1] * K + a[j - 2];

    int max = s[1], min = s[1];

    for (int j = 2; j <= N; j++) {
      a[s[j]] > a[max] ? max = s[j] : 0;
      a[s[j]] < a[min] ? min = s[j] : 0;
    }

    if (max_S != -1) (a[LIMIT] > 0 ? max : min) = max_S;
    write(max, ' '), write(min, '\n');
  }

  return flush(), 0;
}
