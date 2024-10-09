#include <bits/stdc++.h>

constexpr int MOD = 80112002;
constexpr int MAX_N = 5e3 + 5;

int N, M;
std::vector<std::vector<int>> g;

int in[MAX_N];
int f[MAX_N], ans;

void BFS() {
  std::queue<int> q;

  for (int i = 1; i <= N; ++i)
    if (!in[i])
      q.push(i), f[i] = 1;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    if (g[u].empty()) {
      ans = (ans + f[u]) % MOD;
      continue;
    }

    for (int v : g[u]) {
      f[v] = (f[v] + f[u]) % MOD;
      if (!--in[v]) q.push(v);
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;
  g.resize(N + 1);

  while (M--) {
    static int u, v;
    std::cin >> u >> v;
    g[u].push_back(v), ++in[v];
  }

  BFS();

  std::cout << ans << std::flush;
  return 0;
}
