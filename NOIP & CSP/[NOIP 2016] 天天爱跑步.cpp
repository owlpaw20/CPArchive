#include <vector>
#include <iostream>

#define endl '\n'

const int MAX_N = 3e5 + 5;
const int SHIFT = 3e5;

int N, M, w[MAX_N];
std::vector<int> adj[MAX_N];

namespace LCA {
  int size[MAX_N], pref[MAX_N], fa[MAX_N], depth[MAX_N];
  int top[MAX_N], dfn[MAX_N], ts;

  void DFS1(int u, int p) {
    fa[u] = p;
    size[u] = 1;
    depth[u] = depth[p] + 1;
    for (int v : adj[u])
      if (v != p) {
        DFS1(v, u);
        size[u] += size[v];
        if (size[v] > size[pref[u]]) pref[u] = v;
      }
  }

  void DFS2(int u, int t) {
    top[u] = t;
    dfn[u] = ++ts;
    if (!pref[u]) return;
    DFS2(pref[u], t);
    for (int v : adj[u])
      if (v != fa[u] && v != pref[u])
        DFS2(v, v);
  }

  int get_LCA(int u, int v) {
    while (top[u] != top[v])
      if (depth[top[u]] > depth[top[v]]) u = fa[top[u]];
      else v = fa[top[v]];
    return depth[u] < depth[v] ? u : v;
  }
}  // namespace LCA
using namespace LCA;

int st[MAX_N], fn[MAX_N], dist[MAX_N];
int st_cnt[MAX_N], ans[MAX_N];
int buc_1[MAX_N << 1];  // buc_1[p] = 满足起点深度 depth[st] = p 的路径数量
int buc_2[MAX_N << 1];  // buc_2[p] = 满足终点深度 depth[fn] = p 的路径数量

std::vector<int> adj_1[MAX_N], adj_2[MAX_N];

void DFS3(int u) {
  // 从桶里读取贡献
  int t_1 = buc_1[w[u] + depth[u]];
  int t_2 = buc_2[w[u] - depth[u] + SHIFT];

  for (int v : adj[u])
    if (v != fa[u])
      DFS3(v);

  buc_1[depth[u]] += st_cnt[u];  // 上行过程中，当前点作为起点产生贡献，计入桶中
  for (int v : adj_1[u])         // 下行过程中，当前点作为终点产生贡献，计入桶中
    ++buc_2[dist[v] - depth[fn[v]] + SHIFT];

  // 当前节点位置的观察员所获得的总贡献等于当前点的桶中贡献的前后差值
  ans[u] += buc_1[w[u] + depth[u]] - t_1 + buc_2[w[u] - depth[u] + SHIFT] - t_2;

  // 清除以当前节点为起点和终点的线路产生的贡献
  for (int v : adj_2[u]) {
    --buc_1[depth[st[v]]];
    --buc_2[dist[v] - depth[fn[v]] + SHIFT];
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;

  for (int i = 1, u, v; i < N; ++i) {
    std::cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  DFS1(1, 0), DFS2(1, 1);

  for (int i = 1; i <= N; ++i) std::cin >> w[i];

  for (int i = 1; i <= M; ++i) {
    std::cin >> st[i] >> fn[i];
    ++st_cnt[st[i]];  // 统计以每个节点为起点的路径条数

    int lca = get_LCA(st[i], fn[i]);
    dist[i] = depth[st[i]] + depth[fn[i]] - 2 * depth[lca];  // 当前路径的长度

    adj_1[fn[i]].push_back(i);  // 该终点对应的线路集合中加入当前这一条
    adj_2[lca].push_back(i);    // 该 LCA 对应的线路集合中加入当前这一条

    if (depth[lca] + w[lca] == depth[st[i]]) --ans[lca];
  }

  DFS3(1);

  for (int i = 1; i <= N; ++i)
    std::cout << ans[i] << ' ';

  std::cout << endl;
  return fflush(stdout), 0;
}
