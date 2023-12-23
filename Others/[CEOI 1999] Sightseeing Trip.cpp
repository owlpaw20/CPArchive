#include <vector>
#include <cstring>
#include <iostream>
#define endl '\n'
using namespace std;

const int N = 1e2 + 10;
const int INF = 0x1F1F1F1F;
const char* VOID = "No solution.";

int n, m;
int mid[N][N];
vector<int> path;
int g[N][N], dist[N][N];

// 递归地求解 U 和 V 之间的节点
void get_in_between(int u, int v) {
    if (!mid[u][v]) return;  // 如果 U 和 V 之间没有点
    int k = mid[u][v];
    get_in_between(u, k);  // 求前一半
    path.push_back(k);     // 加入中间点 K
    get_in_between(k, v);  // 求后一半
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(g, 0x1F, sizeof g);
    for (int i = 1; i <= n; i++)
        g[i][i] = 0;

    cin >> n >> m;
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u][v] = g[v][u] = min(g[u][v], w);
    }

    int ans = INF;
    memcpy(dist, g, sizeof dist);
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i < k; i++)      // 遍历节点的编号小于上一级的编号
            for (int j = 1; j < i; j++)  // 可以避免重复遍历
                // 找到一个更小的合法三元环
                if (g[i][k] + g[k][j] + dist[i][j] < ans) {
                    ans = g[i][k] + g[k][j] + dist[i][j];  // 存储最短距离
                    // 重新考虑该三元环中间的所有节点
                    path.clear();
                    path.push_back(k);
                    path.push_back(i);
                    get_in_between(i, j);
                    path.push_back(j);
                }
        // 用 Floyd—Warshall 算法更新最短路
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (dist[i][j] > dist[i][k] + dist[k][j])
                    dist[i][j] = dist[i][k] + dist[k][j],
                    mid[i][j] = k;
    }

    if (ans == INF) {
        puts(VOID);  // 无解
    } else {
        for (int i : path)
            cout << i << ' ';
        cout << endl;
    }

    fflush(stdout);
    return 0;
}
