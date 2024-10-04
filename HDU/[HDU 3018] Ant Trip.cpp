#include <bits/stdc++.h>

const int MAX_N = 1e5 + 5;

int fa[MAX_N];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

int deg[MAX_N];
int odd[MAX_N];  // 连通块内奇度点个数

void solve(int N, int M) {
  memset(deg, 0, sizeof(int) * (N + 1));
  memset(odd, 0, sizeof(int) * (N + 1));
  std::iota(fa, fa + N + 1, 0);

  // 处理所有的连通块
  for (int i = 1, u, v; i <= M; ++i) {
    std::cin >> u >> v;
    ++deg[u], ++deg[v];
    fa[find(u)] = find(v);
  }

  // 统计连通块内奇度点的个数
  for (int i = 1; i <= N; ++i)
    if (deg[i] & 1)
      ++odd[find(i)];

  int ans = 0;

  for (int i = 1; i <= N; ++i)
    if (fa[i] == i && deg[i])          // 如果连通块内存在一个以上的节点
      ans += std::max(odd[i] / 2, 1);  // 那么需要对应的笔画数才能覆盖所有边

  std::cout << ans << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int N, M;
  while (std::cin >> N >> M) solve(N, M);

  std::cout.flush();
  return 0;
}
