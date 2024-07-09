#include <numeric>
#include <iostream>

namespace FastIO {
  const int MAX_BUF = 1 << 16;
  char buf[MAX_BUF], *p1, *p2;
  char pbuf[MAX_BUF], *pp = pbuf;

  char getchar() { return (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAX_BUF, stdin), p1 == p2) ? EOF : *p1++); }
  void putchar(char c) { (((pp - pbuf == MAX_BUF) && (fwrite(pbuf, 1, MAX_BUF, stdout), pp = pbuf)), *pp++ = c); }
  void flush() { ((pp - pbuf) && fwrite(pbuf, 1, pp - pbuf, stdout)), fflush(stdout); }

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

using l64 = long long;

const int MAX_N = 1e6 + 5;
const int MAX_V = 1e6 + 5;

int N;
int cnt[MAX_V];
l64 sum_x;

int main() {
  N = read<int>();

  int max_x = 0;
  for (int i = 1, x; i <= N; ++i) {
    ++cnt[x = read<int>()];
    max_x = std::max(max_x, x);
    sum_x += x;  // 统计如果完全不加 TAB 需要多少空格
  }

  // 对于每一种可能的 TAB 宽度，统计前缀空格数量小于等于该值的代码行数之和
  std::inclusive_scan(cnt + 1, cnt + max_x + 1, cnt + 1);

  l64 reduced = 0;  // 通过使用 TAB 替换最多能减少多少个字符

  for (int i = 2; i <= max_x; ++i) {  // 枚举 TAB 宽度
    l64 tmp = 0;

    // 枚举 TAB 数量
    for (int j = 1, lmt = max_x / i; j <= lmt; ++j)
      // 对于每一种 TAB 宽度及数量，统计其能够覆盖多少个原有的空格
      tmp += (l64)j * (cnt[std::min(max_x, i * (j + 1) - 1)] - cnt[i * j - 1]);

    // 计算当前 TAB 宽度能够减少多少个空格的消耗
    // 宽度为 x 的 TAB 可以节省 (x - 1) 个空格的字符数量
    reduced = std::max(reduced, tmp * (i - 1));
  }

  write(sum_x - reduced), putchar('\n');
  return flush(), 0;
}
