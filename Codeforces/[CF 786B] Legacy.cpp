#include <queue>
#include <vector>
#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;
using PII = pair<int, int>;
using PLI = pair<long long, int>;

const int N = 1e5 + 5;
const int SHIFT = N << 2;
const i64 INF = 0x3F3F3F3F3F3F3F3F;

int n, q, s, leaf[N];
vector<PII> graph[N << 3];

#define ul (u << 1)
#define ur (u << 1 | 1)
#define nl node[u].l
#define nr node[u].r

struct SegTree {
  struct {
    int l, r;
  } node[N << 2];

  void build(int l, int r, int u = 1) {
    nl = l, nr = r;

    if (l == r)
      return (void)(leaf[l] = u);  // 标记数组中对应下标所在的叶子节点

    int mid = (l + r) >> 1;

    // 入树为父节点向子节点连边
    graph[u].emplace_back(ul, 0);
    graph[u].emplace_back(ur, 0);

    // 出树为子节点向父节点加边
    graph[ul + SHIFT].emplace_back(u + SHIFT, 0);
    graph[ur + SHIFT].emplace_back(u + SHIFT, 0);

    build(l, mid, ul);
    build(mid + 1, r, ur);
  }

  void connect(int l, int r, int v, int w, bool dir, int u = 1) {
    if (nl >= l && nr <= r) {
      if (dir)
        graph[u + SHIFT].emplace_back(v, w);  // 如果是区间连单点，就在出树上连边
      else
        graph[v].emplace_back(u, w);  // 如果是单点连区间，就在入树上连边
      return;
    }

    int mid = (nl + nr) >> 1;

    if (l <= mid) connect(l, r, v, w, dir, ul);
    if (r > mid) connect(l, r, v, w, dir, ur);
  }
} SGT;

i64 dist[N << 3];
bool vis[N << 3];

void Dijkstra(int st) {
  memset(vis, 0, sizeof vis);
  memset(dist, 0x3F, sizeof dist);

  priority_queue<PLI, vector<PLI>, greater<PLI>> heap;
  heap.emplace(dist[leaf[st] + SHIFT] = 0, leaf[st] + SHIFT);

  while (!heap.empty()) {
    auto [d, u] = heap.top();
    heap.pop();

    if (vis[u]) continue;
    vis[u] = true;

    for (auto [v, w] : graph[u])
      if (dist[v] > d + w)
        heap.emplace(dist[v] = d + w, v);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> q >> s;

  SGT.build(1, n);

  while (q--) {
    int type, a, b, c, d;
    cin >> type >> a >> b >> c;

    if (type == 1)
      graph[leaf[a]].emplace_back(leaf[b], c);  // 单点加边
    else
      cin >> d, SGT.connect(b, c, leaf[a], d, type == 3);  // 区间加边，需要考虑加在哪棵树上
  }

  // 将入树和出树上的相同节点连起来
  for (int i = 1; i <= n; i++) {
    graph[leaf[i]].emplace_back(leaf[i] + SHIFT, 0);
    graph[leaf[i] + SHIFT].emplace_back(leaf[i], 0);
  }

  Dijkstra(s);

  for (int i = 1; i <= n; i++)
    if (dist[leaf[i]] == INF)
      cout << -1 << ' ';
    else
      cout << dist[leaf[i]] << ' ';

  cout << endl;
  return fflush(stdout), 0;
}
