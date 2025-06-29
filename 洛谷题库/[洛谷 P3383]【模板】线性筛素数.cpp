#include <bits/stdc++.h>

namespace FastIO {
  // clang-format off
  const int MAX_BUF = 1 << 20;
  char buf[MAX_BUF], *p1, *p2, pbuf[MAX_BUF], *pp = pbuf;
  char getchar() { return (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAX_BUF, stdin), p1 == p2) ? EOF : *p1++); }
  void putchar(char c) { (((pp - pbuf == MAX_BUF) && (fwrite(pbuf, 1, MAX_BUF, stdout), pp = pbuf)), *pp++ = c); }
  void flush() { (pp - pbuf) && fwrite(pbuf, 1, pp - pbuf, stdout); }
  template <typename T>
  T read() {
    short int f = 1; T var = 0; char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -f; ch = getchar(); }
    while (ch >= '0' && ch <= '9') var = var * 10 + ch - '0', ch = getchar();
    return var * f;
  }
  template <typename T>
  void write(T x) {
    static short int stack[40]; int top = 0;
    if (x < 0) putchar('-'), x = -x;
    do stack[top++] = x % 10, x /= 10; while (x);
    while (top) putchar(stack[--top] + 48);
  }
  // clang-format on
}  // namespace FastIO
using namespace FastIO;

using i64 = long long;

const int MAX_N = 100'000'005;
const int MAX_PI = 5'761'455;

int N, q;
int p[MAX_PI + 5], cnt;
std::bitset<MAX_N> is_composite;

void prep() {
  for (int i = 2; i <= N && (is_composite.test(i) || (p[++cnt] = i)); ++i)
    for (int j = 1; j <= cnt && p[j] * i <= N; ++j)
      if (is_composite.set(p[j] * i), i % p[j] == 0)
        break;
}

int main() {
  N = read<int>(), q = read<int>(), prep();
  while (q--) write(p[read<int>()]), putchar('\n');
  return flush(), 0;
}
