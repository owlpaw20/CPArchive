#include <bits/stdc++.h>

namespace FastIO {
  // clang-format off
  const int MAX_BUF = 1 << 16;
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

const int MAX_N = 3'000'005;

int power(int b, int e, int mod) {
  int res = 1;
  for (; e; e >>= 1)
    ((e & 1) && (res = (i64)res * b % mod)), b = (i64)b * b % mod;
  return res;
}

int N, p;
int fac[MAX_N], ifac[MAX_N];

int main() {
  N = read<int>(), p = read<int>();

  fac[0] = 1;
  for (int i = 1; i <= N; ++i) fac[i] = (i64)fac[i - 1] * i % p;
  ifac[N] = power(fac[N], p - 2, p);
  for (int i = N - 1; ~i; --i) ifac[i] = (i64)ifac[i + 1] * (i + 1) % p;

  for (int i = 1; i <= N; ++i) write((i64)fac[i - 1] * ifac[i] % p), putchar('\n');
  return flush(), 0;
}
