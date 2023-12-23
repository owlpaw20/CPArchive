#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using PDI = pair<double, int>;
using pair_heap = __gnu_pbds::priority_queue<PDI>;

const int N = 2e3 + 10;
const int M = 2e5 + 10;

int n, m, idx;
int ed[M], nx[M], hd[N];
double wt[M], dist[N];
bool vis[N];

void connect(int u, int v, int w) {
    ed[idx] = v;
    wt[idx] = 1.0 - w / 100.0;
    nx[idx] = hd[u];
    hd[u] = idx++;
}

void Dijkstra(int st) {
    memset(vis, false, sizeof vis);
    pair_heap heap;
    heap.push({dist[st] = 1.0, st});
    while (!heap.empty()) {
        int u = heap.top().second;
        heap.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (int i = hd[u]; ~i; i = nx[i]) {
            int j = ed[i];
            if (dist[j] < dist[u] * wt[i])
                heap.push({dist[j] = dist[u] * wt[i], j});
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(8);
    memset(hd, -1, sizeof hd);

    cin >> n >> m;

    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        connect(u, v, w);
        connect(v, u, w);
    }
    int a, b;
    cin >> a >> b;
    Dijkstra(a);
    cout << fixed << 100.0 / dist[b] << endl;
    return 0;
}
