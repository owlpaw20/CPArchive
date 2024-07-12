#include <cstring>
#include <numeric>
#include <iostream>

const int MAX_N = 5e3 + 5;
const int MAX_M = 2e5 + 5;

int N, M;

struct Edge {
  int u, v, w;
} edge[MAX_M];

int fa[MAX_N];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

int Boruvka() {
  static int cheap[MAX_N];   // 每个连通块连接的最小边
  static bool taken[MAX_M];  // 每条边是否已经被使用

  memset(taken, 0, sizeof(bool) * (M + 1));
  int cnt = N, sum = 0;  // 最初每个节点自成一个连通块

  auto cmp = [&](int x, int y) -> bool {
    if (!y) return true;  // 用于特判 cheap[y] 不存在的情况
    if (edge[x].w != edge[y].w) return edge[x].w < edge[y].w;
    return x < y;
  };

  while (true) {
    memset(cheap, 0, sizeof(int) * (N + 1));  // 所有连通块的最小边初始化为 0
    bool flag = false;                        // 如果出现了最小边

    for (int i = 1; i <= M; ++i)
      if (!taken[i]) {
        int u = find(edge[i].u), v = find(edge[i].v);
        if (u == v) continue;
        // 尝试更新该条边两个顶点的最小边
        if (cmp(i, cheap[u])) cheap[u] = i;
        if (cmp(i, cheap[v])) cheap[v] = i;
      }

    for (int i = 1; i <= N; ++i)
      if (cheap[i] && !taken[cheap[i]]) {  // 如果当前节点存在最小边
        flag = true, --cnt;                // 标记最小边出现、连通块数量由于合并而减一
        sum += edge[cheap[i]].w;           // 记录该边给最小生成树带来的权值
        taken[cheap[i]] = true;            // 标记已经使用过

        // 合并连通块
        int fu = find(edge[cheap[i]].u);
        int fv = find(edge[cheap[i]].v);
        fa[fu] = fv;
      }

    if (!flag) break;  // 如果已经不存在最小边则最小生成树已经形成
  }

  // 如果循环结束时只剩下一个连通块，表明存在最小生成树（图连通）
  return (cnt != 1) ? -1 : sum;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;

  for (int i = 1, u, v, w; i <= M; ++i) {
    std::cin >> u >> v >> w;
    edge[i] = (Edge){u, v, w};
  }

  std::iota(fa, fa + N + 1, 0);

  int ans = Boruvka();
  std::cout << (ans == -1 ? "orz" : std::to_string(ans)) << std::endl;

  return 0;
}
