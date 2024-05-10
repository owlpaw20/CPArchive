#include <vector>
#include <iostream>

const int MAX_V = 1e5 + 5;

int N, c[MAX_V];
std::vector<int> adj[MAX_V];

int size[MAX_V], pref[MAX_V];
int dfn[MAX_V], nfd[MAX_V], timestamp;
int ans[MAX_V], cnt[MAX_V], cnt_c;

void add(int u) { cnt_c += !cnt[c[u]]++; }
void del(int u) { cnt_c -= !--cnt[c[u]]; }

// 记录重儿子并预处理 DFS 序
void DFS1(int u, int p) {
  size[u] = 1;
  dfn[u] = ++timestamp;
  nfd[timestamp] = u;

  for (int v : adj[u])
    if (v != p) {
      DFS1(v, u);
      size[u] += size[v];
      if (size[pref[u]] < size[v]) pref[u] = v;
    }
}

// dsu on tree
void DFS2(int u, int p, bool flag) {
  for (int v : adj[u])  // 先处理所有轻子节点，不保存影响但记录答案
    if (v != p && v != pref[u])
      DFS2(v, u, false);

  if (pref[u]) DFS2(pref[u], u, true);  // 处理重子节点，保存影响且记录答案

  for (int v : adj[u])           // 重新处理所有轻子节点，保存影响
    if (v != p && v != pref[u])  // 将轻子节点为根的子树中所有节点全部统计一遍
      for (int i = dfn[v]; i <= dfn[v] + size[v] - 1; ++i)
        add(nfd[i]);

  add(u);          // 统计当前子树的根节点
  ans[u] = cnt_c;  // 记录答案

  if (!flag)  // 如果不保存影响，则清空当前子树遭到的修改
    for (int i = dfn[u]; i <= dfn[u] + size[u] - 1; ++i)
      del(nfd[i]);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;

  for (int i = 1, u, v; i < N; ++i) {
    std::cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  for (int i = 1; i <= N; ++i) std::cin >> c[i];

  DFS1(1, 0);
  DFS2(1, 0, false);

  int M;
  std::cin >> M;

  while (M--) {
    int x;
    std::cin >> x;
    std::cout << ans[x] << '\n';
  }

  return fflush(stdout), 0;
}
