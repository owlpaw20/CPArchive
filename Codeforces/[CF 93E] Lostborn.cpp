#pragma GCC optimize("O2,unroll-loops,inline")

#include <bits/stdc++.h>

namespace FastIO {
  const int MAX_BUF = 1 << 16;
  char buf[MAX_BUF], *p1, *p2;
  char pbuf[MAX_BUF], *pp = pbuf;

  inline char getchar() { return (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAX_BUF, stdin), p1 == p2) ? EOF : *p1++); }
  inline void putchar(char c) { (((pp - pbuf == MAX_BUF) && (fwrite(pbuf, 1, MAX_BUF, stdout), pp = pbuf)), *pp++ = c); }
  inline void flush() { (pp - pbuf) && fwrite(pbuf, 1, pp - pbuf, stdout); }

  template <typename T>
  T read() {
    uint8_t f = 1;
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
    static uint8_t stack[40], top;
    if (x < 0) putchar('-'), x = -x;
    do stack[top++] = x % 10, x /= 10;
    while (x);
    while (top) putchar(stack[--top] + 48);
  }
}  // namespace FastIO
using namespace FastIO;

using i64 = long long;

const int MAX_K = 1e2 + 5;
const i64 LIM = 2e5;

i64 N;
int k, a[MAX_K], lim;
i64 f[LIM + 5][MAX_K];

i64 DFS(i64 i, int j) {
  if (!i) return 0;
  if (j == 1) return i / a[1];
  if (i <= lim && ~f[i][j]) return f[i][j];
  i64 ans = i / a[j] + DFS(i, j - 1) - DFS(i / a[j], j - 1);
  return i <= lim ? f[i][j] = ans : ans;
}

int main() {
  N = read<i64>(), k = read<int>();
  for (int i = 1; i <= k; ++i) a[i] = read<int>();
  std::sort(a + 1, a + k + 1);

  lim = std::min(N, LIM);
  for (int i = 1; i <= lim; ++i) memset(f[i], -1, 8 * (k + 1));

  write(N - DFS(N, k)), putchar('\n');
  return flush(), 0;
}
