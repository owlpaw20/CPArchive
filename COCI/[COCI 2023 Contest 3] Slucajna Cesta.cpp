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

using i64 = long long;

const int MAX_N = 1e6 + 5;
const int MOD = 1e9 + 7;

int N, w[MAX_N];
std::vector<std::vector<int>> g;

// 快速幂
inline int power(int b, int e, int mod = MOD) {
  int res = 1;
  for (; e; e >>= 1) ((e & 1) && (res = (i64)res * b % mod)), b = (i64)b * b % mod;
  return res;
}

// 求逆元
inline int inv(int x) { return power(x, MOD - 2); }

// 模意义减法
inline int sub(i64 x, i64 y) {
  int res = (x - y) % MOD;
  return res < 0 ? res + MOD : res;
}

// f_down[u] 和 f_up[u] 分别表示从 u开始的路径向下走和向上走的概率，ans[u] 保存节点 u 的答案
int f_down[MAX_N], f_up[MAX_N], ans[MAX_N];

// 计算在有 k 个儿子时每个儿子被选到的平均概率
inline int pr(int k) { return (i64)sub(1, power(inv(2), k) + MOD) * inv(k) % MOD; }

// 预处理 f_down[]
void DFS1(int u) {
  i64 prob_v = pr(g[u].size());
  for (int v : g[u]) DFS1(v), f_down[u] = (f_down[u] + (i64)(f_down[v] + w[v]) * prob_v % MOD) % MOD;
}

void DFS2(int u, int fa) {
  // 如果当前节点不为根
  if (fa != 0) {
    i64 prob_fa = pr(g[fa].size());        // 父亲的每一个儿子被选到的概率
    i64 prob_fa_1 = pr(g[fa].size() - 1);  // 除开当前节点，父亲的每一个儿子被选到的概率

    // 如果父节点是根
    // 从 u 向上，需要加上父亲产生的贡献 w[fa]，处理子节点数目减少所产生的概率变化 prob_fa_1 / prob_fa，
    // 并从 f_down[fa] 中减去来自当前节点 u 的那一份即 w[u] + f_down[u]
    if (fa == 1) f_up[u] = (w[fa] + prob_fa_1 * inv(prob_fa) % MOD * sub(f_down[fa], prob_fa * (w[u] + f_down[u])) % MOD) % MOD;

    // 如果父节点不是根
    // 从 u 向上，需要减去当前节点的贡献 prob_fa * (f_up[fa] - (w[u] + f_down[u]))，
    // 即对于选到了 fa 的 u 这个子节点的 prob_fa 的可能性，加上父亲原有的 f_up[fa]，并减去 w[u] + f_down[u] 这个原本来自 u 节点的贡献
    // 然后加上父亲产生的 w[fa] + f_down[fa] 的贡献
    else f_up[u] = (w[fa] + f_down[fa] + prob_fa * sub(f_up[fa], w[u] + f_down[u]) % MOD) % MOD;

    i64 prob_u = pr(g[u].size());        // 所有子节点原始的概率
    i64 prob_u_1 = pr(g[u].size() + 1);  // 子节点增加一个父亲 u 时的概率

    // 统计答案时，首先加上当前节点的权值 w[u]，
    // 加上向上走之后的贡献 prob_u_1 * f_up[u]
    // 加上向下走的贡献 f_down[u] 并处理子节点个数改变所产生的概率变化 prob_u_1 / prob_u
    ans[u] = (w[u] + prob_u_1 * f_up[u] % MOD + prob_u_1 * inv(prob_u) % MOD * f_down[u] % MOD) % MOD;
  }

  else  // 如果当前节点为根则可以直接转移
    ans[u] = (w[u] + f_down[u]) % MOD;

  for (int v : g[u]) DFS2(v, u);
}

int main() {
  N = read<int>(), g.resize(N + 1);
  for (int i = 2; i <= N; ++i) g[read<int>()].push_back(i);
  for (int i = 1; i <= N; ++i) w[i] = read<int>();

  DFS1(1), DFS2(1, 0);
  for (int i = 1; i <= N; ++i) write(ans[i]), putchar('\n');

  return flush(), 0;
}
