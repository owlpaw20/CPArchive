#include <bits/stdc++.h>

const int MAX_N = 5e4 + 5;
const int MAX_M = 1e2 + 5;
const int MAX_K = 25;
const int INF = 0x3F3F3F3F;
const int MAX_ST = 1 << 20;

int N, k, M, len[MAX_M];
bool a[MAX_N];

int loc[MAX_N], idx;
int dist[MAX_N], d[MAX_K][MAX_K];

void BFS(int S) {
  memset(dist, 0x3F, sizeof(int) * (N + 2));
  dist[S] = 0;

  std::queue<int> q;
  q.push(S);

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int i = 1; i <= M; ++i) {
      int v1 = u + len[i], v2 = u - len[i];
      if (v1 <= N + 1 && dist[v1] == INF) dist[v1] = dist[u] + 1, q.push(v1);
      if (v2 >= 1 && dist[v2] == INF) dist[v2] = dist[u] + 1, q.push(v2);
    }
  }

  for (int i = 1; i <= N + 1; ++i)
    if (loc[i])
      d[loc[S]][loc[i]] = dist[i];
}

int f[MAX_ST];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> k >> M;
  for (int i = 1, x; i <= k; ++i) std::cin >> x, a[x] = true;
  for (int i = 1; i <= M; ++i) std::cin >> len[i];
  for (int i = N + 1; i; --i) a[i] ^= a[i - 1];  // 计算异或差分

  for (int i = 1; i <= N + 1; ++i)
    if (a[i])
      loc[i] = ++idx;  // 将所有需要考虑的 1 离散化起来

  for (int i = 1; i <= N + 1; ++i)
    if (a[i])
      BFS(i);  // 通过最短路预处理每一对 1 之间转移的最小花费

  memset(f, 0x3F, sizeof(int) * (1 << idx));
  f[0] = 0;

  // 通过状压 DP 计算将所有 1 都变 0 的最小话费
  for (int ST = 0; ST < (1 << idx); ++ST)
    if (f[ST] != INF)
      for (int i = 0; i < idx; ++i)
        if (!(ST >> i & 1))
          for (int j = i + 1; j < idx; ++j)
            if (!(ST >> j & 1))
              f[ST | (1 << i) | (1 << j)] = std::min(f[ST | (1 << i) | (1 << j)], f[ST] + d[i + 1][j + 1]);

  // 输出答案或报告无解
  std::cout << (f[(1 << idx) - 1] == INF ? -1 : f[(1 << idx) - 1]) << std::flush;
  return 0;
}
