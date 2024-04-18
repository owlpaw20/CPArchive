#include <stack>
#include <queue>
#include <bitset>
#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e4 + 10;
const int M = 1e5 + 10;

int n, m;

// 链式前向星
int ed[M], nx[M], head[N], idx;
int ED[M], NX[M], HEAD[N], IDX;

// Tarjan 缩点
int dfn[N], low[N], scc[N];
int scc_cnt, timestamp;
bool in_stk[N];
stack<int, vector<int>> stk;

// 倍增求 LCA
int depth[N], fa[N][25];

int log2(int x) {
  int exp = 0;
  while (x >>= 1)
    exp += 1;
  return exp;
}

// 原图的加点
void connect(int u, int v) {
  ed[idx] = v;
  nx[idx] = head[u];
  head[u] = idx++;
}

// 缩点后图的加点
void CONNECT(int u, int v) {
  ED[IDX] = v;
  NX[IDX] = HEAD[u];
  HEAD[u] = IDX++;
}

// Tarjan 求无向图的双连通分量
void Tarjan(int u, int fa = 0) {
  dfn[u] = low[u] = ++timestamp;

  stk.push(u);
  in_stk[u] = true;

  for (int i = head[u]; ~i; i = nx[i]) {
    int v = ed[i];
    if (v == fa) continue;  // 二元环不缩点
    if (!dfn[v]) {
      Tarjan(v, u);
      low[u] = min(low[u], low[v]);
    } else if (in_stk[v])
      low[u] = min(low[u], dfn[v]);
  }

  if (dfn[u] == low[u]) {
    scc_cnt++;
    int v;
    do {
      v = stk.top();
      stk.pop();
      in_stk[v] = false;
      scc[v] = scc_cnt;
    } while (v != u);
  }
}

// LCA 的预处理
void BFS(int root) {
  queue<int> q;
  q.push(root);
  depth[root] = 1;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int i = HEAD[u]; ~i; i = NX[i]) {
      int v = ED[i];
      if (depth[v]) continue;

      fa[v][0] = u;
      depth[v] = depth[u] + 1;
      for (int j = 1; j <= log2(n); j++)
        fa[v][j] = fa[fa[v][j - 1]][j - 1];

      q.push(v);
    }
  }
}

// 倍增求 LCA
int LCA(int u, int v) {
  if (depth[u] > depth[v]) swap(u, v);

  for (int i = log2(n); i >= 0; i--)
    if (depth[fa[v][i]] >= depth[u])
      v = fa[v][i];

  if (u == v) return u;

  for (int i = log2(n); i >= 0; i--)
    if (fa[v][i] != fa[u][i])
      v = fa[v][i], u = fa[u][i];

  return fa[u][0];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  memset(head, -1, sizeof head);
  memset(HEAD, -1, sizeof HEAD);

  cin >> n >> m;
  while (m--) {
    int u, v;
    cin >> u >> v;
    connect(u, v);
    connect(v, u);
  }

  for (int i = 1; i <= n; i++)
    if (!dfn[i])
      Tarjan(i);

  for (int i = 1; i <= n; i++)
    for (int j = head[i]; ~j; j = nx[j])
      if (scc[i] != scc[ed[j]])       // 如果这两个点不在同一个双连通分量内
        CONNECT(scc[i], scc[ed[j]]);  // 就分别缩成两个点

  BFS(scc[1]);  // 预处理缩点后图的深度与祖先数组

  int q;
  cin >> q;
  while (q--) {
    int u, v;
    cin >> u >> v;
    u = scc[u], v = scc[v];
    int ans = depth[u] + depth[v] - 2 * depth[LCA(u, v)] + 1;  // 求距离

    // 二进制输出
    bitset<31> s(ans);
    if (s.none())
      cout.put(0);
    else {
      bool flag = false;
      for (int i = 30; i >= 0; i--)
        if (flag || s[i])
          flag = true, cout.put(s[i] + '0');
    }
    cout.put('\n');
  }

  fflush(stdout);
  return 0;
}
