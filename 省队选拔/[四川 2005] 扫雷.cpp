#include <iostream>

using namespace std;

namespace FastIO {
  int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
      if (ch == '-')
        f = -f;
      ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
      x = x * 10 + ch - 48, ch = getchar();
    return x * f;
  }
  void write(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
  }
}  // namespace FastIO
using namespace FastIO;

const int N = 1e4 + 5;

int n;
int f[N][2][2];
// f[i][j][k] 表示位于第 i 行、第 i 行有 j 个地雷、第 i + 1 行有 k 个地雷的总方案数

int main() {
  n = read();

  f[0][0][0] = f[0][0][1] = 1;

  for (int i = 1, t; i <= n; i++) {
    t = read();
    if (t == 0) {
      f[i][0][0] = f[i - 1][0][0];  // 0 0 0
    } else if (t == 1) {
      f[i][0][0] = f[i - 1][1][0];  // 1 0 0
      f[i][1][0] = f[i - 1][0][1];  // 0 1 0
      f[i][0][1] = f[i - 1][0][0];  // 0 0 1
    } else if (t == 2) {
      f[i][1][0] = f[i - 1][1][1];  // 1 1 0
      f[i][0][1] = f[i - 1][1][0];  // 1 0 1
      f[i][1][1] = f[i - 1][0][1];  // 0 1 1
    } else
      f[i][1][1] = f[i - 1][1][1];  // 1 1 1
  }

  write(f[n][1][0] + f[n][0][0]), putchar('\n');
  fflush(stdout);
  return 0;
}
