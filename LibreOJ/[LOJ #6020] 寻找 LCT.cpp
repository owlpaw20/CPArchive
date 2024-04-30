#include <cstring>
#include <numeric>
#include <iostream>
#include <algorithm>

namespace FastIO {
  const int MAX_BUF = 1 << 20;
  char buf[MAX_BUF], *p1, *p2;
  char pbuf[MAX_BUF], *pp = pbuf;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAX_BUF, stdin), p1 == p2) ? EOF : *p1++)
#define putchar(c) (((pp - pbuf == MAX_BUF) && (fwrite(pbuf, 1, MAX_BUF, stdout), pp = pbuf)), *pp++ = c)
#define flush() ((pp - pbuf) && fwrite(pbuf, 1, pp - pbuf, stdout))

  template <typename T>
  inline T read() {
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
  inline void write(T x) {
    static int stack[40];
    int top = 0;
    do stack[top++] = x % 10, x /= 10;
    while (x);
    while (top) putchar(stack[--top] + 48);
  }
}  // namespace FastIO
using namespace FastIO;

const int MAX_V = 1e5 + 5;
const int MAX_E = 2e5 + 5;

int N, K;
int ed[MAX_E], nx[MAX_E], head[MAX_V], idx;
int sizes[MAX_V], sum_s[MAX_V];
int ans[MAX_V];

void connect(int u, int v) {
  ed[idx] = v;
  nx[idx] = head[u];
  head[u] = idx++;
}

namespace Tree {
  int centroid;
  int size[MAX_V], dfn[MAX_V], nfd[MAX_V], ts;

  // 以任意节点为根获取树的重心
  int get_centroid(int u, int p) {
    int sz = 1;     // 以当前节点为根的子树里节点的总数
    int heavy = 0;  // 以当前节点的子节点为根节点的所有子树中节点数量的最大值

    for (int i = head[u], v, sz_v; ~i; i = nx[i]) {
      if ((v = ed[i]) == p) continue;
      sz_v = get_centroid(v, u);
      sz += sz_v, heavy = std::max(heavy, sz_v);
    }

    // 如果当前节点将图分成的两半中，节点数量都不超过总节点数的一半
    // 则根据定义，当前节点为树的重心（题设条件保证本题只有一个重心）
    if (std::max(heavy, N - sz) <= N / 2) centroid = u;
    return sz;
  }

  // 以重心为根处理其所有子节点为根的子树
  void traverse(int u) {
    size[u] = 1;
    dfn[u] = ++ts;
    nfd[ts] = u;

    for (int i = head[u], v; ~i; i = nx[i]) {
      if (dfn[v = ed[i]]) continue;
      traverse(v);
      size[u] += size[v];
    }
  }
}  // namespace Tree
using namespace Tree;

int main() {
  N = read<int>();
  K = read<int>();

  memset(head, -1, sizeof(int) * (N + 1));

  for (int i = 1, u, v; i < N; ++i) {
    u = read<int>(), v = read<int>();
    connect(u, v);
    connect(v, u);
  }

  get_centroid(1, 0);  // 找到重心
  traverse(centroid);  // 处理 DFS 序和子树大小

  int M = 0;
  for (int i = head[centroid]; ~i; i = nx[i]) sizes[++M] = size[ed[i]];
  std::sort(sizes + 1, sizes + M + 1, std::greater<int>());  // 对所有子树按大小排序
  std::inclusive_scan(sizes + 1, sizes + M + 1, sum_s + 1);  // 并作前缀和，以便以较低复杂度 cut 掉前 K 大

  ans[centroid] = 0;  // 原有的重心一定可以成为新树的重心
  // ans 数组存储当前节点需要至少进行多少次 cut-link 操作才能成为重心

  // 枚举原有重心的所有子树
  for (int i = head[centroid], u; ~i; i = nx[i]) {
    int trg_u = N / 2 + 1 - size[u = ed[i]];                                // 当前节点作为新树的重心，还需要 cut 多少条边
    int pos_u = std::lower_bound(sum_s + 1, sum_s + M + 1, trg_u) - sum_s;  // 找到对应节点数量的位置

    if (sizes[pos_u] <= size[u])                                                        // 根节点不能被 cut 掉
      pos_u = std::lower_bound(sum_s + 1, sum_s + M + 1, trg_u + size[u]) - sum_s - 1;  // 如果 cut 了根节点则需要加回来重新选

    // 也有可能是先以原树重心的某个子节点为新树的重心，再花 1 的代价挪到其子树中的某一个节点上
    for (int v = dfn[u]; v <= dfn[u] + size[u] - 1; ++v) {
      int trg_v = N / 2 + 1 - size[nfd[v]];
      int pos_v = std::lower_bound(sum_s + 1, sum_s + M + 1, trg_v) - sum_s;

      if (sizes[pos_v] <= size[u])
        pos_v = std::lower_bound(sum_s + 1, sum_s + M + 1, trg_v + size[u]) - sum_s - 1;

      ans[nfd[v]] = std::min(pos_u + 1, pos_v);
    }
  }

  // 如果需要进行 cut-link 操作的次数小于 K，则可能成为重心
  for (int i = 1; i <= N; ++i) write(ans[i] <= K), putchar('\n');
  flush(), fflush(stdout);
  return 0;
}
