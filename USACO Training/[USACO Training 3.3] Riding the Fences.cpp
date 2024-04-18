#include <vector>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 5e2 + 5;

int m;
int deg[N];
int g[N][N];
vector<int> circ;

void DFS(int u) {
  for (int v = 1; v <= 500; v++)
    if (g[u][v]) {           // 找到最小的可以删的边
      g[u][v]--, g[v][u]--;  // 直接删边
      DFS(v);                // 继续递归
    }
  circ.push_back(u);  // 将起点加入回路中，最终形成逆欧拉回路
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> m;

  while (m--) {
    int u, v;
    cin >> u >> v;
    g[u][v]++, g[v][u]++;
    deg[u]++, deg[v]++;
  }

  int st = 1;
  while (!deg[st]) ++st;  // 如果无向图中没有奇点，则可以以任意有边连接的点作为起点
  for (int i = 1; i <= 500; i++)
    if (deg[i] & 1) {  // 如果无向图中有奇点
      st = i;          // 找到较小的奇点作为起点
      break;           // 由于题目保证有解，所以不用判断是否恰有两个奇点使得欧拉回路存在
    }

  DFS(st);

  for (auto it = circ.rbegin(); it != circ.rend(); it++)
    cout << *it << endl;

  fflush(stdout);
  return 0;
}
