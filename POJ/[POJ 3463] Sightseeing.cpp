#include <queue>
#include <tuple>
#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;
using PII = pair<int, int>;
using TPL = tuple<int, int, int>;

const int N = 1e3 + 10;
const int M = 1e4 + 10;

int n, m, s, e;
int ed[M], nx[M], wt[M], head[N], idx;
int dist[N][2], cnt[N][2];
bool vis[N][2];

void connect(int u, int v, int w) {
    ed[idx] = v;
    wt[idx] = w;
    nx[idx] = head[u];
    head[u] = idx++;
}

int Dijkstra(int s, int e) {
    memset(vis, 0, sizeof vis);
    memset(cnt, 0, sizeof cnt);
    memset(dist, 0x3F, sizeof dist);

    priority_queue<TPL, vector<TPL>, greater<TPL>> heap;
    heap.emplace(dist[s][0] = 1, 0, s);
    cnt[s][0] = 1;

    while (!heap.empty()) {
        auto [d, t, u] = heap.top();
        heap.pop();

        if (vis[u][t]) continue;
        vis[u][t] = true;

        for (int i = head[u]; ~i; i = nx[i]) {
            int v = ed[i], w = wt[i];
            if (dist[v][0] > d + w) {
                heap.emplace(dist[v][1] = dist[v][0], 1, v), cnt[v][1] = cnt[v][0];
                heap.emplace(dist[v][0] = d + w, 0, v), cnt[v][0] = cnt[u][t];
            } else if (dist[v][0] == d + w)
                cnt[v][0] += cnt[u][t];
            else if (dist[v][1] > d + w)
                heap.emplace(dist[v][1] = d + w, 1, v), cnt[v][1] = cnt[u][t];
            else if (dist[v][1] == d + w)
                cnt[v][1] += cnt[u][t];
        }
    }

    return cnt[e][0] + (dist[e][0] + 1 == dist[e][1]) * cnt[e][1];
}

void solve() {
    idx = 0;
    memset(head, -1, sizeof head);

    cin >> n >> m;

    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        connect(u, v, w);
    }

    cin >> s >> e;
    cout << Dijkstra(s, e) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) solve();

    fflush(stdout);
    return 0;
}
