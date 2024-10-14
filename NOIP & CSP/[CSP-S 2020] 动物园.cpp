#include <bits/stdc++.h>

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
    static short int stack[40];
    if (x < 0) putchar('-'), x = -x;
    int top = 0;
    do stack[top++] = x % 10, x /= 10;
    while (x);
    while (top) putchar(stack[--top] + 48);
  }
}  // namespace FastIO
using namespace FastIO;

using i128 = __int128_t;

const int MAX_K = 64;

int N, M, c, k;
bool vis[MAX_K], flag[MAX_K];

int main() {
  N = read<int>(), M = read<int>();
  read<int>(), k = read<int>();

  for (int i = 1; i <= N; ++i) {
    i128 x = read<i128>();
    for (int j = 0; j < k; ++j)
      if (x >> j & 1)
        vis[j] = true;  // 统计有多少二进制位被已有动物覆盖
  }

  while (M--) {
    static int p;
    (p = read<int>()), read<int>();

    // 该条规定的饲料没有被已有动物覆盖，则不能饲养编号在该二进制位上为 1 的动物
    if (!vis[p]) flag[p] = true;
  }

  int cnt = 0;
  for (int i = 0; i < k; ++i) cnt += !flag[i];  // 计算没有限制的二进制位数量

  write(((i128)1 << cnt) - N), flush();
  return 0;
}
