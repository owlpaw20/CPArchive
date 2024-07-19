#include <stack>
#include <vector>
#include <cstring>
#include <iostream>

namespace FastIO {
  const int MAX_BUF = 1 << 20;
  char buf[MAX_BUF], *__p1, *__p2;
  char pbuf[MAX_BUF], *pp = pbuf;

  char getchar() { return (__p1 == __p2 && (__p2 = (__p1 = buf) + fread(buf, 1, MAX_BUF, stdin), __p1 == __p2) ? EOF : *__p1++); }
  void putchar(char c) { (((pp - pbuf == MAX_BUF) && (fwrite(pbuf, 1, MAX_BUF, stdout), pp = pbuf)), *pp++ = c); }
  int flush() { return (pp - pbuf) && fwrite(pbuf, 1, pp - pbuf, stdout), 0; }

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

  template <typename T>
  void write(T x) {
    static int stack[20];
    if (x < 0) putchar('-'), x = -x;
    int top = 0;
    do stack[top++] = x % 10, x /= 10;
    while (x);
    while (top) putchar(stack[--top] + 48);
  }
}  // namespace FastIO
using namespace FastIO;

using LL = long long;

constexpr int MAX_N = 5e5 + 5;
constexpr int MAX_M = 2e6 + 5;
constexpr int MOD = 1e9 + 7;

int p2[MAX_N + MAX_M];

void prep(int N) {
  p2[0] = 1;
  for (int i = 1; i <= N; ++i) p2[i] = (p2[i - 1] * 2) % MOD;
}

int N, M;
int ed[MAX_M], nx[MAX_M], head[MAX_N], idx;
void connect(int u, int v) { ed[idx] = v, nx[idx] = head[u], head[u] = idx++; }

std::stack<int> st;
std::vector<int> dcc[MAX_N];
int dfn[MAX_N], low[MAX_N], bel[MAX_N], vcnt[MAX_N], ts, d_cnt;
bool flag[MAX_N];

// Tarjan 求 e-BCC 并缩点
void Tarjan(int u, int fa = -1) {
  dfn[u] = low[u] = ++ts;
  st.push(u), flag[u] = true;

  for (int i = head[u], v; ~i; i = nx[i]) {
    if ((v = ed[i]) == fa) continue;
    if (!dfn[v]) Tarjan(v, u), low[u] = std::min(low[u], low[v]);
    else if (flag[v]) low[u] = std::min(low[u], dfn[v]);
  }

  if (dfn[u] == low[u]) {  // 如果当前点为边双的顶点
    ++d_cnt;               // 增加边双集合的计数器
    int x;
    do {
      flag[x = st.top()] = false, st.pop();  // 标记出栈
      ++vcnt[bel[x] = d_cnt];                // 统计边双内点的数量
      dcc[d_cnt].push_back(x);               // 将弹出的点加入边双中
    } while (x != u);  // 直到遍历到顶点
  }
}

// 缩点建新图
int ed2[MAX_M], nx2[MAX_M], head2[MAX_N], idx2;
void connect2(int u, int v) { ed2[idx2] = v, nx2[idx2] = head2[u], head2[u] = idx2++; }

int ecnt[MAX_N];      // 边双内的边数
LL ans, f[MAX_N][2];  // 树形 DP 数组
int s_ecnt[MAX_N];    // 新图中以当前点为根的子树中边的数量

// DFS 递归求新图子树内边数
void DFS(int u, int fa = -1) {
  s_ecnt[u] = ecnt[u];  // 当前节点所代表的边双内的所有点都属于子树内
  for (int i = head2[u], v; ~i; i = nx2[i]) {
    if ((v = ed2[i]) == fa) continue;
    DFS(v, u);
    s_ecnt[u] += s_ecnt[v] + 1;  // 加上所有子节点的子树边数以及当前节点到所有子节点的连边
  }
}

// 树形 DP
void fn(int u, int fa = -1) {
  for (int i = head2[u], v; ~i; i = nx2[i]) {
    if ((v = ed2[i]) == fa) continue;
    fn(v, u);
    f[u][1] = (f[u][0] * f[v][1] % MOD + (f[v][0] * 2 + f[v][1]) % MOD * f[u][1] % MOD) % MOD;
    f[u][0] = f[u][0] * f[v][0] % MOD * 2 % MOD;
  }
  // 统计答案
  if (u == 1) ans = (ans + f[u][1]) % MOD;
  else ans = (ans + f[u][1] * p2[s_ecnt[1] - s_ecnt[u] - 1] % MOD) % MOD;
}

int main() {
  N = read(), M = read();
  memset(head, -1, sizeof(int) * (N + 1));

  prep(N + M);  // 预处理 2 的幂

  for (int i = 1, u, v; i <= M; ++i) {
    u = read(), v = read();
    connect(u, v), connect(v, u);
  }

  Tarjan(1);

  memset(head2, -1, sizeof(int) * (d_cnt + 1));

  for (int u = 1; u <= N; ++u)
    for (int i = head[u], v; ~i; i = nx[i])
      if (bel[v = ed[i]] != bel[u]) connect2(bel[u], bel[v]);  // 如果当前点和子节点分属两个边双，就连边
      else ++ecnt[bel[u]];                                     // 如果同属一个边双，则统计边数

  for (int i = 1; i <= d_cnt; ++i) {
    ecnt[i] /= 2;           // 每条边会被统计两次
    f[i][0] = p2[ecnt[i]];  // 初始化树形 DP
    f[i][1] = p2[ecnt[i] + vcnt[i]] - f[i][0];
  }

  DFS(1);
  fn(1);

  write(ans), putchar('\n');
  return FastIO::flush();
}
