#include <bits/stdc++.h>

using PII = std::pair<int, int>;

const int MAX_N = 1e5 + 5;
const int MAX_M = 2e6 + 5;

int N, M, A, B;
int prov_A[MAX_N], prov_B[MAX_N];

int ed[MAX_M], nx[MAX_M], head[MAX_N], idx;
void connect(int u, int v) { ed[idx] = v, nx[idx] = head[u], head[u] = idx++; }

int dfn[MAX_N], low[MAX_N], ts;
std::set<PII> bridge;

void Tarjan(int u, int e) {
  dfn[u] = low[u] = ++ts;

  for (int i = head[u]; ~i; i = nx[i]) {
    int v = ed[i];

    if (!dfn[v]) {
      Tarjan(v, i);
      low[u] = std::min(low[u], low[v]);

      // 将子树中提供 A 和 B 服务的点的数量分别统计起来
      prov_A[u] += prov_A[v], prov_B[u] += prov_B[v];

      if (dfn[u] < low[v])
        // 如果 v 的子树垄断了某种服务或者没有任何服务，那么 (u, v) 为桥
        if (!prov_A[v] || !prov_B[v] || prov_A[v] == A || prov_B[v] == B)
          bridge.emplace(std::min(u, v), std::max(u, v));
    }

    else if (i != (e ^ 1)) low[u] = std::min(low[u], dfn[v]);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M >> A >> B;
  memset(head, -1, sizeof(int) * (N + 1));

  for (int i = 1, x; i <= A; ++i) std::cin >> x, prov_A[x] = 1;
  for (int i = 1, x; i <= B; ++i) std::cin >> x, prov_B[x] = 1;

  while (M--) {
    static int p, q;
    std::cin >> p >> q;
    connect(p, q), connect(q, p);
  }

  Tarjan(1, -1);

  std::cout << bridge.size() << '\n';
  for (auto [u, v] : bridge) std::cout << u << ' ' << v << '\n';

  std::cout.flush();
  return 0;
}
