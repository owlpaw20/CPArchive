#include <stack>
#include <queue>
#include <vector>
#include <cstring>
#include <iostream>

#define endl '\n'

using PII = std::pair<int, int>;

const int MAX_V = 1e4 + 5;
const int MAX_E = 1e5 + 5;

int MAX_N, MAX_M, val[MAX_V], in[MAX_V];

int st[MAX_E], ed[MAX_E], nx[MAX_E], head[MAX_V], idx;
int dist[MAX_V];

std::vector<int> adj[MAX_V];

inline void connect(const int u, const int v) {
  st[idx] = u;
  ed[idx] = v;
  nx[idx] = head[u];
  head[u] = idx++;
}

namespace SCC {
  int timestamp;
  bool vis[MAX_V];
  int dfn[MAX_V], low[MAX_V], gov[MAX_V];

  std::stack<int> stk;

  void Tarjan(int u) {
    dfn[u] = low[u] = ++timestamp;

    stk.push(u);
    vis[u] = true;

    for (int i = head[u]; ~i; i = nx[i]) {
      int v = ed[i];
      if (!dfn[v]) Tarjan(v), low[u] = std::min(low[u], low[v]);
      else if (vis[v]) low[u] = std::min(low[u], low[v]);
    }

    if (low[u] == dfn[u])
      while (!stk.empty()) {
        int v = stk.top();
        stk.pop();
        gov[v] = u;
        vis[v] = false;
        if (u == v) break;
        val[u] += val[v];  // 将强连通分量内部的点权累加到头部节点上
      }
  }
}  // namespace SCC
using namespace SCC;

int topological_sort() {
  std::queue<int> q;

  for (int i = 1; i <= MAX_N; ++i)
    if (gov[i] == i && in[i] == 0)
      q.push(i), dist[i] = val[i];

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v : adj[u]) {
      dist[v] = std::max(dist[v], dist[u] + val[v]);
      if (--in[v] == 0) q.push(v);
    }
  }

  int ret = 0;
  for (int i = 1; i <= MAX_N; ++i)
    ret = std::max(ret, dist[i]);

  return ret;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  memset(head, -1, sizeof head);

  std::cin >> MAX_N >> MAX_M;
  for (int i = 1; i <= MAX_N; ++i) std::cin >> val[i];

  for (int i = 1, u, v; i <= MAX_M; ++i) {
    std::cin >> u >> v;
    connect(u, v);
  }

  // 预处理出所有的强连通分量，有向图中只有环是强连通分量
  for (int i = 1; i <= MAX_N; ++i)
    if (!dfn[i])
      Tarjan(i);

  // 根据强连通分量缩点建新图，用拓扑跑 DAG 上 DP 求最长路
  for (int i = 0; i < MAX_M; ++i) {
    int u = gov[st[i]], v = gov[ed[i]];
    if (u != v) adj[u].push_back(v), ++in[v];
  }

  std::cout << topological_sort() << endl;
  fflush(stdout);
  return 0;
}
