#include <cmath>
#include <cstring>
#include <iostream>

#define endl '\n'

const int MAX_N = 5e4 + 5;

int n;
int sum_f[MAX_N];

int ed[MAX_N], nx[MAX_N], head[MAX_N], idx;
int f[MAX_N], g[MAX_N];
bool vis[MAX_N];

inline void connect(const int u, const int v) {
  ed[idx] = v;
  nx[idx] = head[u];
  head[u] = idx++;
}

void prep(int n) {
  for (int i = 1; i <= n; ++i)
    for (int j = 2, lmt = n / i; j <= lmt; ++j)
      sum_f[i * j] += i;

  for (int i = 2; i <= n; ++i)
    if (i > sum_f[i])
      connect(sum_f[i], i);
}

void DFS(const int u) {
  vis[u] = true;
  for (int i = head[u], v; ~i; i = nx[i]) {
    if (vis[v = ed[i]]) continue;
    DFS(v);
    if (f[u] <= f[v] + 1) {
      g[u] = f[u];
      f[u] = f[v] + 1;
    } else if (g[u] < f[v] + 1)
      g[u] = f[v] + 1;
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  memset(head, -1, sizeof head);

  std::cin >> n;

  prep(n);

  int ans = 0;

  for (int i = 1; i <= n; ++i) {
    if (!vis[i]) DFS(i);
    ans = std::max(ans, f[i] + g[i]);
  }

  std::cout << ans << endl;
  return fflush(stdout), 0;
}
