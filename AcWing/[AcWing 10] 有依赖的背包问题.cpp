#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e2 + 10;

int n, m;
int c[N], v[N], f[N][N];
int ed[N], nx[N], head[N], idx;

void connect(int u, int v) {
  ed[idx] = v;
  nx[idx] = head[u];
  head[u] = idx++;
}

void DFS(int u) {
  for (int i = c[u]; i <= m; i++)
    f[u][i] = v[u];
  for (int i = head[u]; ~i; i = nx[i]) {
    int ver = ed[i];
    DFS(ver);
    for (int j = m; j >= c[u]; j--)
      for (int k = 0; k <= j - c[u]; k++)
        f[u][j] = max(f[u][j], f[u][j - k] + f[ver][k]);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  memset(head, 0xFF, sizeof head);

  cin >> n >> m;
  int root;
  for (int i = 1; i <= n; i++) {
    int q;
    cin >> c[i] >> v[i] >> q;
    if (q == -1)
      root = i;
    else
      connect(q, i);
  }

  DFS(root);

  cout << f[root][m] << endl;
  fflush(stdout);
  return 0;
}
