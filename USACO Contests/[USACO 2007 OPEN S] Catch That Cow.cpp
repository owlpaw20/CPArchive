#include <queue>
#include <vector>
#include <iostream>

using namespace std;
using PII = pair<int, int>;

const int N = 1e5;
const int INF = 0x3F3F3F3F;

int T;
queue<PII> q;
vector<bool> vis;

int BFS(int st, int ed) {
  while (!q.empty()) q.pop();
  q.emplace(st, 0);
  vis[st] = true;

  while (!q.empty()) {
    auto [u, step] = q.front();
    if (u == ed) return step;
    if (u + 1 <= N && !vis[u + 1])
      vis[u + 1] = true, q.emplace(u + 1, step + 1);
    if (u - 1 >= 0 && !vis[u - 1])
      vis[u - 1] = true, q.emplace(u - 1, step + 1);
    if (u * 2 <= N && !vis[u * 2])
      vis[u * 2] = true, q.emplace(u * 2, step + 1);
    q.pop();
  }
  return -1;
}

void solve() {
  int f, c;
  cin >> f >> c;
  vis.assign(N + 5, false);
  cout << BFS(f, c) << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> T;
  while (T--) solve();

  fflush(stdout);
  return 0;
}
