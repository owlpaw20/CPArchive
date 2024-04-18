// 本题同 AcWing-352《闇の連鎖》

/*  把一条非树边加入一棵树中，就会形成一个环
    如果第一步选择切断了 U 到 V 之间的路径上的某条边，
    那么第二步就必须切断这条路径上的非树边，才能使图不联通

    对于每一条树上的边，若有 N 条非树边使其成环， 则称这条树上的边被覆盖了 N 次
    若第一步将被覆盖 0 次的树上边切断，则第二步可切断任意一条附加边，共 M 种方案
    若第一步将被覆盖 1 次的树上边切断，则第二步只能切断对应的非树边，共 1 种方案
    若第一步将被覆盖多次的树上边切断，则第二步无论如何都无法使图不联通

    通过树上差分维护非树边对树上边的覆盖行为：
    树上每个点的初始权值为 0，对于每条非树边，将其起点与终点的权值都 + 1
    将其起点与终点节点的最近公共祖先的权值 - 2（在 LCA 处进入了环）
    最后对整棵树进行一次 DFS，求出以各个节点为根节点的子树中的所有节点的权值和
    即该节点与其父节点之间的树上边被非树边覆盖的次数 */

#include <queue>
#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e5 + 10;
const int M = 2e5 + 10;

int n, m, ans;
int ed[M], nx[M], head[N], idx;
int depth[N], anc[N][20], diff[N];

int log2(int x) {
  float t = (float)n;
  return (*(int *)&t) >> 23 & 31;
}

void connect(int u, int v) {
  ed[idx] = v;
  nx[idx] = head[u];
  head[u] = idx++;
}

void BFS() {
  memset(depth, 0x3F, sizeof depth);
  depth[0] = 0, depth[1] = 1;
  queue<int> q;
  q.push(1);
  while (!q.empty()) {
    int u = q.front();
    for (int i = head[u]; ~i; i = nx[i]) {
      int v = ed[i];
      if (depth[v] > depth[u] + 1) {
        depth[v] = depth[u] + 1;
        q.push(v);
        anc[v][0] = u;
        for (int j = 1; j <= log2(n); j++)
          anc[v][j] = anc[anc[v][j - 1]][j - 1];
      }
    }
    q.pop();
  }
}

int LCA(int u, int v) {
  if (depth[u] > depth[v]) swap(u, v);
  for (int i = log2(n); i >= 0; i--)
    if (depth[anc[v][i]] >= depth[u])
      v = anc[v][i];
  if (u == v) return u;
  for (int i = log2(n); i >= 0; i--)
    if (anc[v][i] != anc[u][i])
      u = anc[u][i], v = anc[v][i];
  return anc[u][0];
}

int DFS(int u) {
  int ret = diff[u];
  for (int i = head[u]; ~i; i = nx[i]) {
    int v = ed[i];
    if (v != anc[u][0]) {
      int s = DFS(v);
      if (s == 0) ans += m;
      if (s == 1) ans += 1;
      ret += s;
    }
  }
  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  memset(head, -1, sizeof head);

  cin >> n >> m;
  for (int i = 1, u, v; i < n; i++) {
    cin >> u >> v;
    connect(u, v);
    connect(v, u);
  }

  BFS();

  for (int i = 1, u, v; i <= m; i++) {
    cin >> u >> v;
    int f = LCA(u, v);
    diff[u] += 1;
    diff[v] += 1;
    diff[f] -= 2;
  }

  DFS(1);

  cout << ans << endl;
  fflush(stdout);
  return 0;
}
