#include <cstring>
#include <iostream>

const int MAX_N = 1e5 + 5;
const int MAX_M = 2e5 + 5;

int N;
int ed[MAX_M], nx[MAX_M], wt[MAX_M], head[MAX_N], idx;

void connect(int u, int v, int w) {
  ed[idx] = v;
  wt[idx] = w;
  nx[idx] = head[u];
  head[u] = idx++;
}

int dist[MAX_N];

void DFS(int u) {
  for (int i = head[u], v; ~i; i = nx[i]) {
    if (dist[v = ed[i]]) continue;
    dist[v] = wt[i] ^ dist[u];
    DFS(v);
  }
}

struct Trie {
  int t[MAX_N * 32][2], idx;

  void ins(int x) {
    for (int i = 31, p = 0, c; ~i; --i) {
      c = (x >> i) & 1;
      if (!t[p][c]) t[p][c] = ++idx;
      p = t[p][c];
    }
  }

  int qry(int x) {
    int sum = 0;
    for (int i = 31, p = 0, c; ~i; --i) {
      c = (x >> i) & 1;
      if (t[p][!c]) sum += (1 << i), p = t[p][!c];
      else p = t[p][c];
    }
    return sum;
  }
} trie;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  memset(head, -1, sizeof(int) * (N + 1));

  for (int i = 1, u, v, w; i < N; ++i) {
    std::cin >> u >> v >> w;
    connect(u, v, w);
    connect(v, u, w);
  }

  dist[1] = 1;
  DFS(1);

  for (int i = 1; i <= N; ++i) trie.ins(dist[i]);

  int ans = 0;
  for (int i = 1; i <= N; ++i)
    ans = std::max(ans, trie.qry(dist[i]));

  std::cout << ans << std::endl;
  return 0;
}
