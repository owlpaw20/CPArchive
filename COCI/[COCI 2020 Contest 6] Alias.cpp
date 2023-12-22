#include <queue>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <unordered_map>

#define endl '\n'

using namespace std;
using PII = pair<int, int>;

const int N = 1e3 + 10;
const long long INF = 1e13;

int n, m, q, idx1, idx2;
int ed[N], nx[N], head[N];
long long wt[N], dist[N];
bool vis[N];
unordered_map<string, int> mir;

void add_edge(int u, int v, long long w) {
    ed[idx1] = v;
    wt[idx1] = w;
    nx[idx1] = head[u];
    head[u] = idx1++;
}

void Dijkstra(int st) {
    for (int i = 1; i <= n; i++) dist[i] = INF;
    memset(vis, 0, sizeof vis);
    dist[st] = 0;
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.emplace(dist[st], st);
    while (!heap.empty()) {
        int u = heap.top().second;
        heap.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = head[u]; ~i; i = nx[i]) {
            int j = ed[i];
            if (dist[j] > dist[u] + wt[i]) {
                dist[j] = dist[u] + wt[i];
                heap.emplace(dist[j], j);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(head, -1, sizeof head);

    cin >> n >> m;

    while (m--) {
        string a, b;
        int t;
        cin >> a >> b >> t;
        if (!mir.count(a)) mir[a] = ++idx2;
        if (!mir.count(b)) mir[b] = ++idx2;
        add_edge(mir[a], mir[b], t);
    }

    cin >> q;

    while (q--) {
        string a, b;
        cin >> a >> b;
        Dijkstra(mir[a]);
        long long ans = dist[mir[b]];
        if (ans == INF) puts("Roger");
        else printf("%lld\n", ans);
    }

    fflush(stdout);
    return 0;
}
