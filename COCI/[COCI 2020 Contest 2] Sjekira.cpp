#include <cstring>
#include <iostream>
#include <algorithm>

#define endl '\n'

using l64 = long long int;
using PII = std::pair<int, int>;

const int MAX_N = 1e5 + 5;
const int MAX_M = 2e5 + 5;

int n;
PII node[MAX_N];

int ed[MAX_M], nx[MAX_M];
int in[MAX_N], head[MAX_N], idx;

inline void connect(const int u, const int v) {
  ed[idx] = v;
  nx[idx] = head[u];
  head[u] = idx++;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  memset(head, -1, sizeof head);

  std::cin >> n;

  for (int i = 1; i <= n; ++i)
    std::cin >> node[i].first, node[i].second = i;

  for (int i = 1, u, v; i < n; ++i) {
    std::cin >> u >> v;
    connect(u, v), ++in[v];
    connect(v, u), ++in[u];
  }

  std::sort(node + 1, node + n + 1, std::greater<PII>());

  l64 ans = 0;

  for (int i = 1; i <= n; ++i) {
    auto [deg, id] = node[i];
    ans += (l64)deg * (in[id] + (i != 1));
    for (int j = head[id]; ~j; j = nx[j]) --in[ed[j]];
  }

  std::cout << ans << endl;
  fflush(stdout);
  return 0;
}
