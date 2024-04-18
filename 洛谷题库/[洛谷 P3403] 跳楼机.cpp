#include <queue>
#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;
using PII = pair<i64, i64>;

const int N = 2e5 + 5;

i64 h;
int x, y, z;
int ed[N], nx[N], wt[N], head[N], idx;
i64 dist[N];  // 只使用操作 2 和 3 最低能够到达的楼层，且 dist[i] % x = i
bool vis[N];

void connect(int u, int v, int w) {
  ed[idx] = v;
  wt[idx] = w;
  nx[idx] = head[u];
  head[u] = idx++;
}

void Dijkstra(int st) {
  memset(dist, 0x3F, sizeof dist);
  priority_queue<PII, vector<PII>, greater<PII>> heap;

  heap.emplace(dist[st] = 1, st);

  while (!heap.empty()) {
    auto [d, u] = heap.top();
    heap.pop();

    if (vis[u]) continue;
    vis[u] = true;

    for (int i = head[u]; ~i; i = nx[i])
      if (dist[ed[i]] > dist[u] + wt[i])
        heap.emplace(dist[ed[i]] = dist[u] + wt[i], ed[i]);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  memset(head, -1, sizeof head);

  cin >> h;
  cin >> x >> y >> z;

  if (x == 1 || y == 1 || z == 1)  // 如果有 1 显然可以到达任意楼层
    return cout << h << endl, 0;

  for (int i = 0; i < x; i++) {  // 从 0 开始方便取模
    connect(i, (i + y) % x, y);  // 当前楼层可以通过操作 2 跳到 x 层内的哪一层
    connect(i, (i + z) % x, z);  // 当前楼层可以通过操作 3 跳到 x 层内的哪一层
  }

  Dijkstra(1);

  i64 ans = 0;
  for (int i = 0; i < x; i++)
    if (h >= dist[i])                // 只统计操作后仍在高度限制内的情况
      ans += (h - dist[i]) / x + 1;  // 将所有跳得到的楼层全部统计下来

  cout << ans << endl;
  return fflush(stdout), 0;
}
