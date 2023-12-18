#include <queue>
#include <cstring>
#include <iostream>
#include <unordered_set>

using namespace std;
using PII = pair<int, int>;

const int N = 105;
const int M = N * N * 2;
const int INF = 0x3f3f3f3f;

bool excl[N][N], vis[N];
int n, k, m, s, t, idx;
int head[N], c[N], dist[N];
int ed[M], wt[M], nx[M];

void connect(int u, int v, int w) {
    ed[idx] = v;
    wt[idx] = w;
    nx[idx] = head[u];
    head[u] = idx++;
}

void Dijkstra(int st) {
    memset(dist, 0x3f, sizeof dist);
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.emplace(dist[st] = 0, st);
    while (!heap.empty()) {
        int u = heap.top().second;
        heap.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (int i = head[u]; ~i; i = nx[i]) {
            int v = ed[i];
            if (dist[v] > dist[u] + wt[i])
                heap.emplace(dist[v] = dist[u] + wt[i], v);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(head, -1, sizeof head);

    cin >> n >> k >> m >> s >> t;
    for (int i = 1; i <= n; i++) cin >> c[i];
    for (int i = 1; i <= k; i++)
        for (int j = 1; j <= k; j++)
            cin >> excl[i][j];

    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        if (!excl[c[v]][c[u]]) connect(u, v, w);
        if (!excl[c[u]][c[v]]) connect(v, u, w);
    }

    Dijkstra(s);

    if (dist[t] == INF || c[s] == c[t]) cout << -1 << endl;
    else cout << dist[t] << endl;
    return 0;
}
