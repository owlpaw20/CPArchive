#include <cstring>
#include <iostream>
#include <algorithm>

constexpr int MAX_N = 1e5 + 5;
constexpr int MAX_M = 2e5 + 5;

int N, w[MAX_N];
int ed[MAX_M], nx[MAX_M], head[MAX_N], idx;

void connect(int u, int v) { ed[++idx] = v, nx[idx] = head[u], head[u] = idx; }

int f[MAX_N];

void DFS(int u, int fa = 0) {
  int sum = 0;
  for (int i = head[u], v; ~i; i = nx[i]) {
    if ((v = ed[i]) == fa) continue;
    DFS(v, u);
    sum += f[v];
  }
  f[u] = std::max(w[u] + sum, 0);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  memset(head, -1, sizeof(int) * (N + 1));

  bool all_negative = true;
  for (int i = 1; i <= N; ++i) std::cin >> w[i], all_negative &= (w[i] < 0);
  for (int i = 1, u, v; i < N; ++i) std::cin >> u >> v, connect(u, v), connect(v, u);

  DFS(1);

  if (!all_negative) std::cout << *std::max_element(f + 1, f + N + 1) << std::endl;
  else std::cout << *std::max_element(w + 1, w + N + 1) << std::endl;
  return 0;
}
