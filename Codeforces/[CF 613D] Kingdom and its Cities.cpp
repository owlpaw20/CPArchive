#pragma GCC optimize("O2,unroll-loops,inline")

#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_set>

#define endl '\n'

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
    if (x < 0) putchar('-'), x = -x;
    int top = 0;
    do stack[top++] = x % 10, x /= 10;
    while (x);
    while (top) putchar(stack[--top] + 48);
  }
}  // namespace FastIO
using namespace FastIO;

const int MAX_V = 1e5 + 5;

int N;
std::vector<int> city, aux;
std::vector<int> adj[MAX_V], adjv[MAX_V];

int size[MAX_V], pref[MAX_V], fa[MAX_V], depth[MAX_V];
int dfn[MAX_V], top[MAX_V], ts;

bool g[MAX_V];
std::unordered_set<int> key;

void DFS1(int u, int p) {
  fa[u] = p;
  size[u] = 1;
  depth[u] = depth[p] + 1;

  for (int v : adj[u])
    if (v != p) {
      DFS1(v, u);
      size[u] += size[v];
      if (size[pref[u]] < size[v]) pref[u] = v;
    }
}

void DFS2(int u, int t) {
  top[u] = t;
  dfn[u] = ++ts;

  if (!pref[u]) return;
  DFS2(pref[u], t);

  for (int v : adj[u])
    if (v != pref[u] && v != fa[u])
      DFS2(v, v);
}

int query_LCA(int u, int v) {
  while (top[u] != top[v])
    if (depth[top[u]] > depth[top[v]]) u = fa[top[u]];
    else v = fa[top[v]];
  return (depth[u] < depth[v]) ? u : v;
}

// 虚树 DP
// f[x] 为 x 为根节点时使给定 K 个点互相不连通的最小删点数
// g[x] 为此时是否有关键点直接连接到 x 的父亲
int DP(int u) {
  int f_u = 0, key_cnt = 0;

  for (int v : adjv[u])
    f_u += DP(v), key_cnt += g[v];

  if (key.count(u)) f_u += key_cnt, g[u] = true;  // 若 u 是关键点，则所有有关键点的子树都需要断开
  else if (key_cnt > 1) f_u += 1, g[u] = false;   // 若 u 不是关键点且子树中关键点超过一个，则当前节点需要删除
  else g[u] = key_cnt;                            // 若 u 不是关键点且子树中关键点不超过一个，则当前节点没有必要删除

  return adjv[u].clear(), f_u;  // 在线清空邻接表以节省时间
}

int main() {
  N = read<int>();

  for (int i = 1, u, v; i < N; ++i) {
    u = read<int>(), v = read<int>();
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  // 预处理树剖求 LCA
  DFS1(1, 0), DFS2(1, 1);

  int Q = read<int>();

  // 虚树中节点的顺序以在原树中的 DFS 序为基础
  auto cmp = [&](int x, int y) { return dfn[x] < dfn[y]; };

  while (Q--) {
    int K = read<int>();

    city.resize(K), key.clear();
    aux.clear(), aux.reserve(K << 1);

    for (int i = 0; i < K; ++i)
      key.insert(city[i] = read<int>());

    // 如果有任意一对关键点为直接亲子关系，则显然一定无解
    bool flag = false;

    for (int c : city)
      if (key.count(fa[c])) {
        flag = true;
        break;
      }

    if (flag) {
      write(-1), putchar('\n');
      continue;
    }

    // 根据 DFS 序对原树中的节点进行排序
    std::sort(city.begin(), city.end(), cmp);

    // 将关键点和关键点有关的 LCA 插入虚树序列中
    for (int i = 0; i < K - 1; ++i)
      aux.push_back(city[i]),
        aux.push_back(query_LCA(city[i], city[i + 1]));
    aux.push_back(city[K - 1]);

    // 根据 DFS 序进行排序并去重
    std::sort(aux.begin(), aux.end(), cmp);
    aux.erase(std::unique(aux.begin(), aux.end()), aux.end());

    memset(g, 0, sizeof(bool) * (N + 1));

    for (size_t i = 0, LCA; i < aux.size() - 1; ++i) {
      LCA = query_LCA(aux[i], aux[i + 1]);
      adjv[LCA].emplace_back(aux[i + 1]);  // 从 LCA 向关键点连边
    }

    write(DP(aux.front())), putchar('\n');  // 在虚树上 DP 求解
  }

  flush(), fflush(stdout);
  return 0;
}
