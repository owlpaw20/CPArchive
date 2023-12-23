#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;

using PII = pair<int, int>;
const int N = 15e3 + 10;

int n, m, s, t, u, v, w, idx;
int ed[N], nx[N], wt[N], head[N], dist[N];
bool vis[N];

void connect(int u, int v, int w) {
    ed[idx] = v;
    wt[idx] = w;
    nx[idx] = head[u];
    head[u] = idx++;
}

int Dijkstra() {
    dist[s] = 0;
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.emplace(dist[s], s);
    while (!heap.empty()) {
        int u = heap.top().second;
        heap.pop();
        if (vis[u])
            continue;
        vis[u] = 1;
        for (int i = head[u]; ~i; i = nx[i]) {
            int j = ed[i];
            if (dist[j] > dist[u] + wt[i]) {
                dist[j] = dist[u] + wt[i];
                heap.emplace(dist[j], j);
            }
        }
    }
    return dist[t];
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n >> m >> s >> t;
    memset(head, -1, sizeof head);
    memset(dist, 0x3F, sizeof dist);
    while (m--) {
        cin >> u >> v >> w;
        connect(u, v, w);
        connect(v, u, w);
    }
    cout << Dijkstra() << endl;
    return 0;
}
