#include <bits/stdc++.h>

using i64 = long long;

const int MAX_N = 1e5 + 5;

int N, a[MAX_N], loc[MAX_N];
std::vector<std::vector<int>> g;

int maxsub[MAX_N];
int st[MAX_N], ed[MAX_N], ts;

void DFS1(int u, int f) {
  maxsub[u] = a[u];  // 初始化子树中的最大权值
  st[u] = ++ts;      // 记录初次进入节点时的 DFS 序

  for (int v : g[u])
    if (v != f)
      DFS1(v, u), maxsub[u] = std::max(maxsub[u], maxsub[v]);  // 更新 maxsub

  ed[u] = ts;  // 记录末次离开节点时的 DFS 序
}

bool vis[MAX_N];
i64 ans, C, D;

void DFS2(int u, int v, int mex, int max) {
  vis[u] = vis[v] = true;             // 标记链的两个端点已被访问
  max = std::max({max, a[u], a[v]});  // 将 max 用当前链两端点的权值进行更新

  while (vis[loc[mex]]) {  // 判断更高的 mex 值是否已经在链上出现
    ++mex;                 // 如果已经出现则更新目标 mex 为 mex + 1

    // 尝试延展当前状态的链。由于链上已经有 0 到 mex - 1 的所有元素，
    // 所以无论怎样延长 mex 都不会变小（如果能够变大就会继续递归与循环并更新答案）。
    // 在这种情况下我们考虑最大化 max 值，也就是在现有链的两个端点的子树中寻找最大权值点，
    // 并将其作为当前 mex 下最优链的两个端点来统计答案。

    int tmp = max;
    for (int k : g[u]) vis[k] || (tmp = std::max(tmp, maxsub[k]));
    for (int k : g[v]) vis[k] || (tmp = std::max(tmp, maxsub[k]));

    // 更新答案
    ans = std::max(ans, C * mex + D * tmp);
  }

  int k = loc[mex];  // 记录当前 mex 所在节点

  // check(p, c) 返回的值表示 p 是否为 c 的上级节点
  auto check = [&](int p, int c) { return st[p] <= st[c] && ed[p] >= ed[c]; };

  // 判断当前 mex 所在节点是否在当前链可以延伸的范围（当前两端点的子树）内。
  // 如果可以的话，这表示我们可以延长链来更新 mex，于是枚举其所在的子节点子树，并递归进入。

  if (check(u, k))
    for (int t : g[u])
      if (!vis[t] && check(t, k))
        return DFS2(t, v, mex, max);

  if (check(v, k))
    for (int t : g[v])
      if (!vis[t] && check(t, k))
        return DFS2(u, t, mex, max);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> C >> D, g.resize(N + 1);
  for (int i = 1; i <= N; ++i) std::cin >> a[i], loc[a[i]] = i;

  for (int i = 1, u, v; i < N; ++i) {
    std::cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  DFS1(loc[0], -1);
  DFS2(loc[0], loc[0], 0, 0);  // 以权值为 0 的节点作为链的初始状态

  std::cout << ans << std::flush;
  return 0;
}
