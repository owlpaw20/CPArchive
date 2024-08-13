#pragma GCC optimize("O2,unroll-loops,inline")

#include <bits/stdc++.h>

const int MAX_N = 3e5 + 5;

struct randHash {
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

int N, M, k;
bool vis[MAX_N];
std::unordered_set<int, randHash> fbd[MAX_N];

// 对于每一个连通块，用其中的某一个节点作为连通块的代表，存入 rep 集合
std::unordered_set<int, randHash> rep;

bool BFS(int S) {
  std::queue<int> q;
  q.emplace(S), vis[S] = true;

  // 标记连通块内是否至少存在一个节点可以与树根存在连边
  bool flag = false;

  while (!q.empty()) {
    static std::stack<int, std::vector<int>> tmp;

    int u = q.front();
    q.pop();

    for (int v : rep)                                 // 考虑所有未访问的节点是否可以放入当前连通块
      if (v != u && !vis[v] && !fbd[u].count(v))      // 如果没有被访问过且不与当前节点禁止连边
        vis[v] = true, q.emplace(v), tmp.emplace(v);  // 则标记它已经被访问，并准备将其从 rep 集合中删去

    while (!tmp.empty()) rep.erase(tmp.top()), tmp.pop();  // 将当前连通块内非代表的节点从 rep 集合中删去
    if (!fbd[u].count(1)) flag = true;                     // 如果当前连通块内任意节点可以与树根建立连边，则该连通块与主树连通
  }

  return flag;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M >> k;

  for (int i = 1, u, v; i <= M; ++i) {
    std::cin >> u >> v;
    fbd[u].emplace(v), fbd[v].emplace(u);

    if (u == 1 || v == 1) {     // 如果树根允许连边的数量已经小于 k 了
      static int root_fbd = 0;  // 则显然不合法
      if (k > N - 1 - ++root_fbd) goto fail;
    }
  }

  // 将树根以外的节点预先放进 rep 集合中等待发落
  for (int i = 2; i <= N; ++i) rep.emplace(i);

  for (int i = 2; i <= N; ++i)
    if (!vis[i] && rep.count(i))  // 对于每一个新的连通块
      if (!BFS(i))                // 考虑其是否与树根连通
        goto fail;                // 如果不与树根连通，则不可能构成连通图

  if ((int)rep.size() > k)  // 如果在处理连通块后，连通块数量（也就是连通块代表的数量）大于 k
    goto fail;              // 根节点连出去的边也一定大于 k，因此不合法

  std::cout << "possible" << std::flush;
  return 0;

fail:
  std::cout << "impossible" << std::flush;
  return 0;
}
