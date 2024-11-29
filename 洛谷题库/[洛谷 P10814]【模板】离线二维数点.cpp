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

using TUP = std::tuple<int, int, int>;

const int MAX_N = 2'000'000;

int N, M;
int a[MAX_N + 5];

std::vector<std::vector<TUP>> qd(MAX_N + 5);
int ans[MAX_N + 5];

struct Fenwick {
  int c[MAX_N + 5];
  void upd(int x) { for (; x <= MAX_N && ++c[x]; x += x & -x); }
  int qry(int x) {
    int sum = 0;
    for (; x; x -= x & -x) sum += c[x];
    return sum;
  }
} fwk;

int main() {
  N = read<int>(), M = read<int>();
  for (int i = 1; i <= N; ++i) a[i] = read<int>();

  for (int i = 1, l, r, x; i <= M; ++i) {
    l = read<int>(), r = read<int>(), x = read<int>();
    qd[l - 1].emplace_back(x, -1, i);
    qd[r].emplace_back(x, 1, i);
  }

  for (int i = 1; i <= N && (fwk.upd(a[i]), true); ++i)
    for (auto [x, v, id] : qd[i])
      ans[id] += v * fwk.qry(x);

  for (int i = 1; i <= M; ++i) write(ans[i]), putchar('\n');
  return flush(), 0;
}
