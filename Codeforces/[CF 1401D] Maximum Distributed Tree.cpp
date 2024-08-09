#include <bits/stdc++.h>

using i64 = long long;

const int MAX_N = 2e5 + 5;
const int MAX_M = 4e5 + 5;
const int MAX_P = 6e4 + 5;
const int MOD = 1e9 + 7;

int N;
int ed[MAX_M], nx[MAX_M], head[MAX_N], idx;
void connect(int u, int v) { ed[idx] = v, nx[idx] = head[u], head[u] = idx++; }

int size[MAX_N];
std::priority_queue<i64> heap;

void DFS(int u, int fa = -1) {
  size[u] = 1;
  for (int i = head[u]; ~i; i = nx[i]) {
    int v = ed[i];
    if (v == fa) continue;
    DFS(v, u), size[u] += size[v];
    heap.emplace((i64)size[v] * (N - size[v]));
  }
}

int p[MAX_P];

void solve() {
  std::cin >> N, idx = 0;
  memset(head, -1, sizeof(int) * (N + 1));

  for (int i = 1, u, v; i < N; ++i) {
    std::cin >> u >> v;
    connect(u, v);
    connect(v, u);
  }

  DFS(1);

  int M;
  std::cin >> M;

  for (int i = 1; i <= M; ++i) std::cin >> p[i];
  std::sort(p + 1, p + M + 1);

  while (M >= N) p[M - 1] = (i64)p[M - 1] * p[M] % MOD, --M;

  int ans = 0;

  while (M) ans = (ans + heap.top() % MOD * p[M--] % MOD) % MOD, heap.pop();
  while (!heap.empty()) ans = (ans + heap.top() % MOD) % MOD, heap.pop();

  std::cout << ans << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) solve();

  std::cout.flush();
  return 0;
}
