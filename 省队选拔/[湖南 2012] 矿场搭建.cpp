#include <bits/stdc++.h>

using u64 = unsigned long long;

const int MAX_N = 1e3 + 5;

int N, M;
std::unordered_map<int, std::vector<int>> g;

bool is_cut[MAX_N];
int dfn[MAX_N], low[MAX_N], ts;

// 求出图中所有的割点
void Tarjan(int u, int fa) {
  dfn[u] = low[u] = ++ts;
  int child_cnt = 0;

  for (int v : g[u])
    if (!dfn[v]) {
      Tarjan(v, u), ++child_cnt;
      low[u] = std::min(low[u], low[v]);
      is_cut[u] = low[v] >= dfn[u];
    } else
      low[u] = std::min(low[u], dfn[v]);

  if (fa == -1 && child_cnt == 1) is_cut[u] = false;
}

int ncut, cut;
int color[MAX_N];

// 遍历图中每一个点双并统计其中割点和非割点的数量
void DFS(int u, int c) {
  color[u] = c, ++ncut;
  for (int v : g[u]) {
    if (is_cut[v] && color[v] != c) ++cut, color[v] = c;  // 割点不递归，求出的是点双
    if (!color[v]) DFS(v, c);                             // 非割点递归统计
  }
}

bool solve(int T) {
  std::cin >> M;
  if (!M) return false;

  N = 0;
  g = std::unordered_map<int, std::vector<int>>();

  for (int i = 1, u, v; i <= M; ++i) {
    std::cin >> u >> v;
    N = std::max({N, u, v});
    g[u].push_back(v);
    g[v].push_back(u);
  }

  ts = 0;
  memset(dfn, 0, sizeof(int) * (N + 1));
  memset(low, 0, sizeof(int) * (N + 1));
  memset(is_cut, 0, sizeof(bool) * (N + 1));

  for (int i = 1; i <= N; ++i)
    if (!dfn[i])
      Tarjan(i, -1);

  int ans1 = 0;
  u64 ans2 = 1;
  memset(color, 0, sizeof(int) * (N + 1));

  for (int i = 1, c = 0; i <= N; ++i) {
    if (color[i] || is_cut[i]) continue;
    ncut = cut = 0;
    DFS(i, ++c);

    // 如果点双边界上没有割点，则需要在其中设置两个出口，以防一个出口塌陷
    // 如果点双边界上仅有一个割点，那么需要在某个非割点处设置一个出口，如果出口塌陷则可以通过割点到达其他点双
    // 如果点双边界上有两个及以上的割点，那么无论在何处塌陷都能跑到某一个割点并到达其他点双，无需设置出口
    if (!cut) ans1 += 2, ans2 *= ncut * (ncut - 1) / 2;
    else if (cut == 1) ans1 += 1, ans2 *= ncut;
  }

  std::cout << std::format("Case {}: {} {}\n", T, ans1, ans2);
  return true;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T = 0;
  while (solve(++T));

  std::cout.flush();
  return 0;
}
