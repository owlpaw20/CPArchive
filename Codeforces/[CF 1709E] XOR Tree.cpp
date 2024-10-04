#include <bits/stdc++.h>

const int MAX_N = 2e5 + 5;

int N, a[MAX_N];
std::vector<std::vector<int>> g;

struct MyHash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
};

int ans, b[MAX_N];  // b[i] 为从根节点到节点 i 路径上点权的异或和
std::vector<std::unordered_set<int, MyHash>> set;

void DFS(int u, int f) {
  set[u].insert(b[u] = b[f] ^ a[u]);  // 将当前点的 b 值存到当前子树的集合中

  bool contains_bad_path = false;

  for (int v : g[u])
    if (v != f)
      DFS(v, u);

  // 树上启发式合并
  for (int v : g[u]) {
    if (v == f) continue;
    if (set[u].size() < set[v].size()) std::swap(set[u], set[v]);

    // 如果当前子树的集合中存在与 a[u] 异或后和为 0 的元素，说明需要修改根的权值使得异或和非 0
    for (int b : set[v]) contains_bad_path |= set[u].count(b ^ a[u]);
    for (int b : set[v]) set[u].insert(b);
  }

  // 如果修改了根的权值，由于可以随意修改，所以该子树内再不可能出现任何异或和为 0 的链的端点
  if (contains_bad_path) ++ans, set[u].clear();
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  g.resize(N + 1), set.resize(N + 1);
  for (int i = 1; i <= N; ++i) std::cin >> a[i];

  for (int i = 1, u, v; i < N; ++i) {
    std::cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  DFS(1, 0);

  std::cout << ans << std::flush;
  return 0;
}
