#include <cstring>
#include <iostream>
#include <algorithm>

#define endl '\n'

const int MAX_V = 5e4 + 5;
const int MAX_E = 1e5 + 5;

int N, K;
int ed[MAX_E], nx[MAX_E], head[MAX_V], idx;
int d[MAX_V];

inline void connect(const int u, const int v) {
  ed[idx] = v;
  nx[idx] = head[u];
  head[u] = idx++;
}

namespace HLD {
  int fa[MAX_V], size[MAX_V], pref[MAX_V], depth[MAX_V];
  int top[MAX_V];

  void DFS1(int u, int p) {
    fa[u] = p;
    size[u] = 1;
    depth[u] = depth[p] + 1;

    for (int i = head[u], v; ~i; i = nx[i]) {
      if ((v = ed[i]) == p) continue;
      DFS1(v, u);
      size[u] += size[v];
      if (size[pref[u]] < size[v]) pref[u] = v;
    }
  }

  void DFS2(int u, int t) {
    top[u] = t;

    if (!pref[u]) return;
    DFS2(pref[u], t);

    for (int i = head[u], v; ~i; i = nx[i])
      if (v = ed[i], (v != fa[u] && v != pref[u]))
        DFS2(v, v);
  }

  int query_LCA(int u, int v) {
    while (top[u] != top[v])
      if (depth[top[u]] < depth[top[v]]) v = fa[top[v]];
      else u = fa[top[u]];
    return depth[u] > depth[v] ? v : u;
  }
}  // namespace HLD
using namespace HLD;

void calc(int u) {
  for (int i = head[u], v; ~i; i = nx[i]) {
    if ((v = ed[i]) == fa[u]) continue;
    calc(v);
    d[u] += d[v];
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> K;

  memset(head, -1, sizeof(int) * (N + 1));

  for (int i = 1, u, v; i < N; ++i) {
    std::cin >> u >> v;
    connect(u, v);
    connect(v, u);
  }

  DFS1(1, 0);
  DFS2(1, 1);

  for (int i = 1, u, v; i <= K; ++i) {
    std::cin >> u >> v;
    int LCA = query_LCA(u, v);
    ++d[u], ++d[v], --d[LCA], --d[fa[LCA]];
  }

  calc(1);

  std::cout << *std::max_element(d + 1, d + N + 1) << endl;
  fflush(stdout);
  return 0;
}
