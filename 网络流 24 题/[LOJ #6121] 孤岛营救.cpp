#include <set>
#include <deque>
#include <cstring>
#include <iostream>

#define x first
#define y second
#define endl '\n'

using namespace std;

using PII = pair<int, int>;

const int N = 15;
const int M = 4e2;
const int P = 1 << 10;

int n, m, k, p;
int head[N * N], ed[M], wt[M], nx[M], idx;
int Hash[N][N], key[N * N];
int dist[N * N][P];
bool vis[N * N][P];
set<PII> edges;

void connect(int u, int v, int w) {
  ed[idx] = v;
  wt[idx] = w;
  nx[idx] = head[u];
  head[u] = idx++;
}

void build() {
  const int dx[] = {-1, 0, 1, 0};
  const int dy[] = {0, 1, 0, -1};
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      for (int k = 0; k < 4; k++) {
        int x = i + dx[k], y = j + dy[k];
        if (x < 1 || x > n || y < 1 || y > m) continue;
        int u = Hash[i][j], v = Hash[x][y];
        if (!edges.count({u, v}))  // 如果这两个方格之间没有门或墙
          connect(u, v, 0);        // 则连一条零权边表示可以直接到达
      }
}

int BFS() {
  memset(dist, 0x3f, sizeof dist);
  dist[1][0] = 0;

  deque<PII> q;         // first = 当前位置的哈希值，second = 当前持有钥匙的状态
  q.push_back({1, 0});  // 起始状态：Hash(1, 1) = 1，此时未持有钥匙

  while (!q.empty()) {
    PII t = q.front();
    q.pop_front();

    if (vis[t.x][t.y]) continue;
    vis[t.x][t.y] = true;

    if (t.x == n * m)         // 如果已经到达终点
      return dist[t.x][t.y];  // 就退出搜索并返回最短路

    if (key[t.x]) {                             // 如果当前位置有钥匙
      int state = t.y | key[t.x];               // 则记录状态
      if (dist[t.x][state] > dist[t.x][t.y]) {  // 如果当前位置的状态可以更新
        dist[t.x][state] = dist[t.x][t.y];      // 则更新
        q.push_front({t.x, state});             // 并放到队首立即处理
      }
    }

    for (int i = head[t.x]; ~i; i = nx[i]) {
      int j = ed[i];
      if (wt[i] && !(t.y >> (wt[i] - 1) & 1)) continue;  // 如果有门但没有对应的钥匙则不前进
      if (dist[j][t.y] > dist[t.x][t.y] + 1) {
        dist[j][t.y] = dist[t.x][t.y] + 1;  // 更新最短路
        q.push_back({j, t.y});              // 常规则放到队尾
      }
    }
  }

  return -1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  memset(head, -1, sizeof head);

  cin >> n >> m >> p >> k;

  // 矩阵哈希值
  for (int i = 1, t = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      Hash[i][j] = t++;

  while (k--) {
    int x1, y1, x2, y2, c;
    cin >> x1 >> y1 >> x2 >> y2 >> c;
    int u = Hash[x1][y1], v = Hash[x2][y2];
    edges.insert({u, v}), edges.insert({v, u});  // 将门和墙存入 set 中
    if (c) connect(u, v, c), connect(v, u, c);   // 如果是门，则单独保存其类别并连边
  }

  build();  // 建图

  int s;
  cin >> s;
  while (s--) {
    int x, y, c;
    cin >> x >> y >> c;
    key[Hash[x][y]] |= 1 << (c - 1);  // 钥匙编号从 0 开始，进行状态压缩
  }

  cout << BFS() << endl;
  fflush(stdout);
  return 0;
}
