#include <bits/stdc++.h>

namespace FastIO {
  const int MAX_BUF = 1 << 16;
  char buf[MAX_BUF], *p1, *p2;

  char getchar() { return (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAX_BUF, stdin), p1 == p2) ? EOF : *p1++); }

  template <typename T = int>
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
}  // namespace FastIO
using namespace FastIO;

const int MAX_N = 1e5 + 5;

int N, M;
int a[MAX_N];

int fa[MAX_N];                 // flag 标记该点是否有一个长度为 1 的自环，该节点可以自己处理偶数的增减
bool flag[MAX_N], val[MAX_N];  // val = 1 表示可以同时增加或减少，0 表示可以一增一减

int dsu_find(int x) {
  if (fa[x] == x) return x;
  int fx = dsu_find(fa[x]);
  val[x] ^= val[fa[x]];
  return fa[x] = fx;
}

void dsu_merge(int x, int y, bool type) {
  // 计算两个点之间路径的异或和，作为合并之后子节点的权值
  int fx = dsu_find(x), fy = dsu_find(y), d = val[x] ^ type ^ val[y];
  // 如果是自环且长度为一，则更新 flag 标记；
  // 否则将 flag 标记传导到根节点，表明该连通块内有一个点可以用来消化偶数的增减
  fx == fy ? flag[fx] |= (d == 1) : fa[fx] = fy, val[fx] = d, flag[fy] |= flag[fx];
}

void solve() {
  N = read(), M = read();
  for (int i = 1; i <= N; ++i) a[i] = read();
  for (int i = 1; i <= N; ++i) a[i] = read() - a[i];

  std::iota(fa, fa + N + 1, 0);
  memset(val, 0, sizeof(bool) * (N + 1));
  memset(flag, 0, sizeof(bool) * (N + 1));

  while (M--) {
    static int type, x, y;
    type = read(), x = read(), y = read();
    dsu_merge(x, y, type & 1);
  }

  for (int i = 1, f; i <= N; ++i)
    // 对于所有非连通块根的节点
    if ((f = dsu_find(i)) != i)
      // 如果 val = 1，则将根节点与当前节点同时更改；
      // 否则将当前节点更改为目标值，并将另一边贡献传递到根节点等待处理
      val[i] ? a[f] -= a[i] : a[f] += a[i];

  for (int i = 1; i <= N; ++i)
    // 如果在传导并用奇环消化之后根节点的权值依然无法清空
    if (fa[i] == i && (flag[i] && (a[i] %= 2), a[i]))
      return puts("NO"), void();  // 则不合法

  puts("YES");
}

int main() {
  int T = read();
  while (T--) solve();
  return 0;
}
