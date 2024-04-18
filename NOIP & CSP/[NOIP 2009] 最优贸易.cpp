#include <queue>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;
const int M = 1e6 + 10;

struct Graph {
  queue<int> q;
  int head[N], ed[M], nx[M];
  bool access[N];
  int idx;

  void init() {
    idx = 0;
    memset(head, -1, sizeof head);
  }

  void connect(int u, int v) {
    ed[idx] = v;
    nx[idx] = head[u];
    head[u] = idx++;
  }

  void BFS(int st) {
    access[st] = true;
    q.push(st);
    while (!q.empty()) {
      int u = q.front();
      for (int i = head[u]; ~i; i = nx[i]) {
        int v = ed[i];
        if (!access[v])
          access[v] = 1, q.push(v);
      }
      q.pop();
    }
  }

  void mark(int st, int *arr, int wt) {
    arr[st] = wt;
    q.push(st);
    while (!q.empty()) {
      int u = q.front();
      for (int i = head[u]; ~i; i = nx[i]) {
        int v = ed[i];
        if (!arr[v])
          arr[v] = wt, q.push(v);
      }
      q.pop();
    }
  }
};

Graph G, H;
int n, m, c[N], seq[N];
int mindist[N], maxdist[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    cin >> c[i];

  G.init(), H.init();
  while (m--) {
    int u, v, type;
    cin >> u >> v >> type;
    G.connect(u, v), H.connect(v, u);
    if (type == 2)
      G.connect(v, u), H.connect(u, v);
  }

  G.BFS(1), H.BFS(n);

  for (int i = 1; i <= n; i++) seq[i] = i;
  sort(seq + 1, seq + n + 1, [&](int x, int y) {
    return c[x] < c[y];
  });

  for (int i = 1; i <= n; i++)
    if (!mindist[seq[i]] && G.access[seq[i]] == true)
      G.mark(seq[i], mindist, c[seq[i]]);
  for (int i = n; i >= 1; i--)
    if (!maxdist[seq[i]] && H.access[seq[i]] == true)
      H.mark(seq[i], maxdist, c[seq[i]]);

  int ans = 0;
  for (int i = 1; i <= n; i++)
    if (G.access[i] && H.access[i])
      ans = max(ans, maxdist[i] - mindist[i]);

  cout << ans << endl;
  return 0;
}
