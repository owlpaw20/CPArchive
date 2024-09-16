#include <bits/stdc++.h>

const int MAX_N = 1e6 + 5;
const int MAX_M = 2e6 + 5;

int N;
int ed[MAX_M], nx[MAX_M], head[MAX_N], idx;
void connect(int u, int v) { ed[idx] = v, nx[idx] = head[u], head[u] = idx++; }

int dfn[MAX_N], ver[MAX_N], ts;
int size[MAX_N], depth[MAX_N], pref[MAX_N];

void DFS1(int u, int fa) {
  size[u] = 1;
  depth[u] = depth[fa] + 1;
  dfn[u] = ++ts, ver[ts] = u;

  for (int i = head[u], v; ~i; i = nx[i]) {
    if ((v = ed[i]) != fa) {
      DFS1(v, u);
      size[u] += size[v];
      if (size[v] > size[pref[u]]) pref[u] = v;
    }
  }
}

int ans[MAX_N], cnt[MAX_N];
int max_cnt, min_depth;

// 统计节点 u 的贡献
void contribute(int u) {
  ++cnt[depth[u]];
  if (cnt[depth[u]] > max_cnt) max_cnt = cnt[depth[u]], min_depth = depth[u];
  else if (cnt[depth[u]] == max_cnt) min_depth = std::min(min_depth, depth[u]);
}

void DFS2(int u, int fa, bool keep) {
  // 先递归到轻子节点，计算其答案，不保留贡献
  for (int i = head[u], v; ~i; i = nx[i])
    if (v = ed[i], (v != fa && v != pref[u]))
      DFS2(v, u, false);

  // 递归到重子节点，计算答案并保留贡献
  if (pref[u]) DFS2(pref[u], u, true);

  // 将轻子节点的贡献加上
  for (int i = head[u], v; ~i; i = nx[i])
    if (v = ed[i], (v != fa && v != pref[u]))
      for (int j = dfn[v]; j <= dfn[v] + size[v] - 1; ++j)
        contribute(ver[j]);

  contribute(u);                  // 统计根的贡献
  ans[u] = min_depth - depth[u];  // 记录当前节点的答案

  if (!keep) {  // 如果不保留贡献，则回滚对 cnt 数组的修改
    for (int i = dfn[u]; i <= dfn[u] + size[u] - 1; ++i) --cnt[depth[u]];
    min_depth = max_cnt = 0;
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  memset(head, -1, sizeof(int) * (N + 1));
  for (int i = 1, u, v; i < N; ++i) std::cin >> u >> v, connect(u, v), connect(v, u);

  DFS1(1, 0);
  DFS2(1, 0, true);

  for (int i = 1; i <= N; ++i) std::cout << ans[i] << '\n';

  std::cout.flush();
  return 0;
}
