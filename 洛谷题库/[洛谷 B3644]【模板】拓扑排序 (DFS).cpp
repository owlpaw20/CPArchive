#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;

const int N = 1e2 + 5;

int n;
vector<bool> vis;
vector<vector<int>> edges;

void DFS(int u, vector<int> &seq) {
  vis[u] = true;
  for (int v : edges[u])
    if (!vis[v])
      DFS(v, seq);
  seq.push_back(u);
}

vector<int> topological_sort() {
  vector<int> seq;

  for (int u = 1; u <= n; u++)
    if (!vis[u])
      DFS(u, seq);

  reverse(seq.begin(), seq.end());
  return seq;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  vis.resize(n + 1);
  edges.resize(n + 1);

  for (int i = 1, j; i <= n; i++)
    while (cin >> j, j)
      edges[i].push_back(j);

  vector<int> ret = topological_sort();

  for (int u : ret)
    cout << u << ' ';

  cout << endl;
  fflush(stdout);
  return 0;
}
