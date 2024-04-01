#include <vector>
#include <cstring>
#include <iostream>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/assoc_container.hpp>

#define endl '\n'

using namespace std;
using i64 = long long;
using PII = pair<int, int>;
using pair_heap = __gnu_pbds::priority_queue<PII, greater<PII>, __gnu_pbds::pairing_heap_tag>;

const int N = 8e2 + 10;
const int M = 3e3 + 10; // 两倍空间
const int INF = 0x3F3F3F3F;

int n, m, p, idx;
int dist[N], hd[N];
int ed[M], nx[M], wt[M];
bool vis[N];
vector<int> where;

void connect(int u, int v, int w) {
    ed[idx] = v;
    wt[idx] = w;
    nx[idx] = hd[u];
    hd[u] = idx++;
}

void Dijkstra(int st) {
    memset(dist, 0x3F, sizeof dist);
    memset(vis, false, sizeof vis);
    pair_heap heap;
    heap.push({dist[st] = 0, st});
    while (!heap.empty()) {
        int u = heap.top().second;
        heap.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (int i = hd[u]; ~i; i = nx[i]) {
            int j = ed[i];
            if (dist[j] > dist[u] + wt[i])
                heap.push({dist[j] = dist[u] + wt[i], j});
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(hd, -1, sizeof hd);

    cin >> n >> m >> p;
    where.resize(n);
    for (int& i : where) cin >> i;

    while (p--) {
        int u, v, w;
        cin >> u >> v >> w;
        connect(u, v, w);
        connect(v, u, w);
    }

    i64 ans = INF;
    for (int i = 1; i <= m; i++) {
        Dijkstra(i);
        i64 sum = 0;
        for (int j : where)
            sum += dist[j];
        if (sum >= INF) continue;
        ans = min(ans, sum);
    }

    cout << ans << endl;
    return 0;
}
