#include <vector>
#include <iostream>

using l64 = long long;

const int MAX_V = 1e5 + 5;

int N, c[MAX_V];
std::vector<int> adj[MAX_V];

int size[MAX_V], pref[MAX_V];
int cnt[MAX_V], max, b;
l64 sum, ans[MAX_V];

void DFS1(int u, int p) {
  size[u] = 1;
  for (int v : adj[u])
    if (v != p) {
      DFS1(v, u), size[u] += size[v];
      if (size[pref[u]] < size[v]) pref[u] = v;
    }
}

// 处理所有修改
void modify(int u, int p, int val) {
  cnt[c[u]] += val;                                  // 在桶的对应位置加上当前节点的编号
  if (cnt[c[u]] > max) max = cnt[c[u]], sum = c[u];  // 更新最大值
  else if (cnt[c[u]] == max) sum += c[u];            // 更新次大值

  for (int v : adj[u])
    if (v != p && v != b)  // 避免递归重子节点
      modify(v, u, val);
}

void DFS2(int u, int p, bool flag) {
  for (int v : adj[u])
    if (v != p && v != pref[u])
      DFS2(v, u, false);

  if (pref[u]) DFS2(pref[u], u, true), b = pref[u];

  modify(u, p, 1);

  b = 0;
  ans[u] = sum;

  if (!flag) {  // 复原
    modify(u, p, -1);
    sum = max = 0;
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  for (int i = 1; i <= N; ++i) std::cin >> c[i];
  for (int i = 1, u, v; i < N; ++i) {
    std::cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  DFS1(1, 0);
  DFS2(1, 0, true);

  for (int i = 1; i <= N; ++i)
    std::cout << ans[i] << ' ';

  std::cout << '\n';
  return fflush(stdout), 0;
}
