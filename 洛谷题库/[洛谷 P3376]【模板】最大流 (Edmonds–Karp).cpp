#include <queue>
#include <cstring>
#include <iostream>

using LL = long long;

const int MAX_N = 2e2 + 5;
const int MAX_M = 5e3 + 5;
const LL INF = 1e18;

int N, M, S, T;
int ed[MAX_M << 1], nx[MAX_M << 1], head[MAX_N], idx;
int loc[MAX_N][MAX_N], pre[MAX_N];
LL cap[MAX_N], ca[MAX_M << 1], ans;

void connect(int u, int v, int c) {
  ed[idx] = v, ca[idx] = c, nx[idx] = head[u], head[u] = idx++;
  ed[idx] = u, ca[idx] = 0, nx[idx] = head[v], head[v] = idx++;
}

bool EdmondsKarp(int st = S, int fn = T) {
  static bool vis[MAX_N];
  memset(vis, 0, sizeof(bool) * (N + 1));
  memset(cap, 0, sizeof(LL) * (N + 1));

  std::queue<int> q;
  q.push(st), cap[st] = INF;

  auto update_flow = [&](int s = S, int t = T) -> void {
    int u = t;
    while (u != s) {
      int i = pre[u];
      ca[i] -= cap[t];
      ca[i ^ 1] += cap[t];
      u = ed[i ^ 1];
    }
    ans += cap[t];
  };

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    if (vis[u]) continue;
    vis[u] = true;

    if (u == fn) return update_flow(st, fn), true;

    for (int i = head[u], v; ~i; i = nx[i]) {
      if (!ca[i] || vis[v = ed[i]]) continue;
      cap[v] = std::min<LL>(cap[u], ca[i]);
      pre[v] = i;
      q.push(v);
    }
  }

  return false;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M >> S >> T;
  memset(head, -1, sizeof(int) * (N + 1));
  for (int i = 0; i <= N; ++i) memset(loc[i], -1, sizeof(int) * (N + 1));

  while (M--) {
    static int u, v, c;
    std::cin >> u >> v >> c;
    if (loc[u][v] == -1) loc[u][v] = idx, connect(u, v, c);
    else ca[loc[u][v]] += c;
  }

  while (EdmondsKarp()) continue;

  std::cout << ans << std::endl;
  return 0;
}
