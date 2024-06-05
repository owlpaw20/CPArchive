#include <iostream>

namespace FastIO {
  const int MAX_BUF = 1 << 20;
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
}  // namespace FastIO
using namespace FastIO;

using LL = long long;

const int MAX_N = 5e6 + 5;
const int MOD1 = 1e9 + 7;
const int MOD2 = 998244353;

int N, a[MAX_N];
LL prod_a[MAX_N];
LL prod_inv[MAX_N];

template <typename intT, typename bufT = __int128_t>
intT power(intT b, intT e, intT mod) {
  intT res = 1;
  while (e) ((e & 1) && (res = (bufT)res * b % mod)), b = (bufT)b * b % mod, e >>= 1;
  return res;
}

int main() {
  N = read<int>();
  for (int i = 1; i <= N; ++i) a[i] = read<int>();

  prod_a[0] = 1;
  for (int i = 1; i <= N; ++i) prod_a[i] = prod_a[i - 1] * a[i] % MOD1;

  prod_inv[N] = power<int, LL>(prod_a[N], MOD1 - 2, MOD1);

  for (int i = N; i; --i) prod_inv[i - 1] = prod_inv[i] * a[i] % MOD1;

  LL ans = 0;
  for (int i = 1; i <= N; ++i) {
    ans = ans * MOD2 % MOD1;
    ans = (ans + prod_inv[i] * prod_a[i - 1]) % MOD1;
  }

  write(ans), putchar('\n');
  return flush(), 0;
}
