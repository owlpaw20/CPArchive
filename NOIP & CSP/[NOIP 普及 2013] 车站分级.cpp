#include <queue>
#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e3 + 10;
const int M = 1e6 + 10;

int n, m, idx, ans;
int ed[M], nx[M], head[N], indeg[N], depth[N], a[N];
bool vis[N], flag[N][N];

void connect(int u, int v) {
  ed[idx] = v;
  nx[idx] = head[u];
  head[u] = idx++;
}

void topological_sort() {
  queue<int> q;

  for (int i = 1; i <= n; i++)
    if (!indeg[i])
      q.push(i), depth[i] = 1;

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = head[u]; ~i; i = nx[i]) {
      int j = ed[i];
      depth[j] = depth[u] + 1;
      ans = max(ans, depth[j]);
      indeg[j] -= 1;
      if (indeg[j] == 0) q.push(j);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  memset(head, -1, sizeof head);

  cin >> n >> m;
  while (m--) {
    int s;
    cin >> s;
    memset(a, 0, sizeof a);
    memset(vis, false, sizeof vis);
    for (int i = 1; i <= s; i++)
      cin >> a[i], vis[a[i]] = true;
    for (int i = a[1] + 1; i <= a[s]; i++)
      if (!vis[i])
        for (int j = 1; j <= s; j++)
          if (!flag[i][a[j]])
            indeg[a[j]]++, connect(i, a[j]), flag[i][a[j]] = true;
  }

  topological_sort();

  cout << ans << endl;
  fflush(stdout);
  return 0;
}
