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

const int MAX_N = 5'000'005;

int N, p, k;
int a[MAX_N], pre_p[MAX_N], suf_p[MAX_N];

int power(int b, int e, int mod) {
  int res = 1;
  for (; e; e >>= 1)
    ((e & 1) && (res = (i64)res * b % mod)), b = (i64)b * b % mod;
  return res;
}

int main() {
  N = read<int>(), p = read<int>(), k = read<int>();
  for (int i = 1; i <= N; ++i) a[i] = read<int>();

  pre_p[0] = suf_p[N + 1] = 1;
  for (int i = 1; i <= N; ++i) pre_p[i] = (i64)pre_p[i - 1] * a[i] % p;
  for (int i = N; i >= 1; --i) suf_p[i] = (i64)suf_p[i + 1] * a[i] % p;

  int ans = 0;

  for (int i = 1, coeff = 1; i <= N; ++i) {
    coeff = (i64)coeff * k % p;
    (ans += (i64)pre_p[i - 1] % p * suf_p[i + 1] % p * coeff % p) %= p;
  }

  write((i64)ans * power(pre_p[N], p - 2, p) % p);
  return flush(), 0;
}
