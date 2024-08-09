#include <bits/stdc++.h>

const int MAX_N = 1e4 + 5;
const int MAX_M = 2e4 + 5;
const int MAX_K = 12;

int N, S, K;
int ed[MAX_M], nx[MAX_M], wt[MAX_M], head[MAX_N], idx;
void connect(int u, int v, int w) { ed[idx] = v, wt[idx] = w, nx[idx] = head[u], head[u] = idx++; }

int f[MAX_N][MAX_K];  // f[i][j] 表示节点 i 被至少 1 个机器人访问，向其子节点安排 j 个机器人并且不返回的最小花费

void DFS(int u, int fa) {
  for (int i = head[u]; ~i; i = nx[i]) {
    int v = ed[i];
    if (v == fa) continue;

    DFS(v, u);

    for (int j = K; ~j; --j) {         // 枚举可供安排的机器人数量
      f[u][j] += f[v][0] + 2 * wt[i];  // 不向当前子节点额外安排机器人，则当前位置的机器人需要往来连接子节点的边两次
      for (int k = 1; k <= j; ++k)     // 向当前子节点安排 k 个机器人，则从子节点处计算贡献，并且加上所有机器人前往子节点的边权
        f[u][j] = std::min(f[u][j], f[u][j - k] + f[v][k] + k * wt[i]);
    }
  }
}

void solve() {
  memset(head, -1, sizeof(int) * (N + 1)), idx = 0;
  for (int i = 0; i <= N; ++i) memset(f[i], 0, sizeof(int) * (K + 1));

  for (int i = 1, u, v, w; i < N; ++i) {
    std::cin >> u >> v >> w;
    connect(u, v, w);
    connect(v, u, w);
  }

  DFS(S, -1);

  std::cout << f[S][K] << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  while (std::cin >> N >> S >> K) solve();

  std::cout.flush();
  return 0;
}
