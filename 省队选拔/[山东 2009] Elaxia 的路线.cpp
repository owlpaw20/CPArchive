#include <queue>
#include <vector>
#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;
using PII = pair<int, int>;

const int N = 1.5e3 + 5;
const int M = 6e5 + 5;

int n, m;
int x1, y1, x2, y2;

namespace SP {
    int ed[M], wt[M], nx[M], head[N], idx;
    int dist[4][N];
    bool vis[N];

    void connect(int u, int v, int w) {
        ed[idx] = v;
        wt[idx] = w;
        nx[idx] = head[u];
        head[u] = idx++;
    }

    void Dijkstra(int st, int k) {
        memset(vis, 0, sizeof vis);
        memset(dist[k], 0x3F, sizeof dist[k]);

        priority_queue<PII, vector<PII>, greater<PII>> heap;
        heap.emplace(dist[k][st] = 0, st);

        while (!heap.empty()) {
            auto [d, u] = heap.top();
            heap.pop();

            if (vis[u]) continue;
            vis[u] = true;

            for (int i = head[u]; ~i; i = nx[i]) {
                int v = ed[i];
                if (dist[k][v] > dist[k][u] + wt[i])
                    heap.emplace(dist[k][v] = dist[k][u] + wt[i], v);
            }
        }
    }

    void build_edge();
}  // namespace SP

namespace LP {
    int ed[M], wt[M], nx[M], head[N], idx;
    int f[N];
    bool used[N];

    void connect(int u, int v, int w) {
        ed[idx] = v;
        wt[idx] = w;
        nx[idx] = head[u];
        head[u] = idx++;
        used[u] = used[v] = true;
    }

    // 树上 DP 求最长链
    int DFS(int u) {
        if (f[u]) return f[u];

        for (int i = head[u]; ~i; i = nx[i])
            f[u] = max(f[u], DFS(ed[i]) + wt[i]);

        return f[u];
    }

    int get_longest_path() {
        for (int i = 1; i <= n; i++)
            if (used[i] && !f[i])  // 如果这个点出现在了最短路树上并且第一次更新
                DFS(i);            // 就尝试用该点更新最长链

        int ret = 0;
        for (int i = 1; i <= n; i++)
            ret = max(ret, f[i]);  // 统计所有以任意点为起点的最长链中的最长链

        return ret;
    }
}  // namespace LP

void SP::build_edge() {
    for (int u = 1; u <= n; u++)
        for (int i = head[u]; ~i; i = nx[i]) {
            int v = ed[i], w = wt[i];

            // 如果从 s 到 t 的最短路上，有一条有向边 (u -> v) 使得
            // (s -> u) + (u -> v) + (t -> v) == (s -> t)，
            // 就说明这条边在最短路树上

            if (dist[0][u] + dist[1][v] + w == dist[0][y1] ||
                dist[0][v] + dist[1][u] + w == dist[0][y1]) {
                // 由于存储的是有向边，可能漏判其中一种情况
                if (dist[2][u] + dist[3][v] + w == dist[2][y2]) LP::connect(u, v, w);
                if (dist[2][v] + dist[3][u] + w == dist[2][y2]) LP::connect(v, u, w);
            }
        }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(SP::head, -1, sizeof SP::head);
    memset(LP::head, -1, sizeof LP::head);

    cin >> n >> m;
    cin >> x1 >> y1 >> x2 >> y2;

    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        SP::connect(u, v, w);
        SP::connect(v, u, w);
    }

    // 求四个源点为起点的最短路
    SP::Dijkstra(x1, 0);
    SP::Dijkstra(y1, 1);
    SP::Dijkstra(x2, 2);
    SP::Dijkstra(y2, 3);

    // 将出现在最短路树上的所有边全部建边
    SP::build_edge();

    // 求最短路树上的最长链
    cout << LP::get_longest_path() << endl;
    return fflush(stdout), 0;
}
