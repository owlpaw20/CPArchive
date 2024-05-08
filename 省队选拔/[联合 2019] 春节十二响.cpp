#include <queue>
#include <vector>
#include <iostream>

#define endl '\n'

using l64 = long long;

const int MAX_V = 2e5 + 5;

int N, w[MAX_V];
std::vector<int> adj[MAX_V], tmp;
std::priority_queue<int> heap[MAX_V];
// 如果使用 PBDS，则 swap 必须使用成员函数才能保证复杂度 O(1)

// 思路参考：https://www.cnblogs.com/RabbitHu/p/10816732.html
// 思路参考：https://www.luogu.com.cn/problem/solution/P5290

void join(int x, int y) {
  if (heap[x].size() < heap[y].size()) std::swap(heap[x], heap[y]);
  while (!heap[y].empty()) {
    tmp.push_back(std::max(heap[x].top(), heap[y].top()));
    heap[x].pop(), heap[y].pop();
  }
  while (!tmp.empty()) heap[x].push(tmp.back()), tmp.pop_back();
}

void DFS(int u) {
  for (int v : adj[u]) DFS(v), join(u, v);
  heap[u].push(w[u]);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  for (int i = 1; i <= N; ++i) std::cin >> w[i];
  for (int i = 2, v; i <= N; ++i) std::cin >> v, adj[v].push_back(i);

  DFS(1);

  l64 ans = 0;
  while (!heap[1].empty()) ans += heap[1].top(), heap[1].pop();

  std::cout << ans << endl;
  return fflush(stdout), 0;
}
