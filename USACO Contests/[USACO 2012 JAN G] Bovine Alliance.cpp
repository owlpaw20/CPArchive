#include <bits/stdc++.h>

using LL = long long;

const int MAX_N = 1e5 + 5;
const int MOD = 1e9 + 7;

int N, M;
std::vector<int> adj[MAX_N];

int v_cnt, e_cnt;
bool vis[MAX_N];

void DFS(int u) {
  vis[u] = true, ++v_cnt;
  for (int v : adj[u]) {
    ++e_cnt;
    if (!vis[v]) DFS(v);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;

  while (M--) {
    static int u, v;
    std::cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  LL ans = 1;

  for (int i = 1; i <= N; ++i) {
    if (vis[i]) continue;

    v_cnt = 0, e_cnt = 0;
    DFS(i);

    if (v_cnt == e_cnt / 2) (ans *= 2) %= MOD;
    else if (v_cnt > e_cnt / 2) (ans *= v_cnt) %= MOD;
    else if (v_cnt < e_cnt / 2) return putchar('0'), 0;
  }

  std::cout << ans << std::flush;
  return 0;
}
