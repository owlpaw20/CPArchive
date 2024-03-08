#include <queue>
#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;
using PII = pair<i64, int>;

const int N = 1e3 + 5;
const int M = 2e4 + 5;
const int INF = 0x3F3F3F3F;

int n, m, L, s, t;
int st[M], ed[M], wt[M], nx[M], head[N], idx;
bool is_zero[M], vis[N];
i64 dist1[N], dist2[N];

void connect(int u, int v, int w, bool z) {
    is_zero[idx] = z;
    st[idx] = u;
    ed[idx] = v;
    wt[idx] = w;
    nx[idx] = head[u];
    head[u] = idx++;
}

void Dijkstra1(int st) {
    memset(dist1, 0x3F, sizeof dist1);

    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.emplace(dist1[st] = 0, st);

    while (!heap.empty()) {
        auto [d, u] = heap.top();
        heap.pop();

        if (vis[u]) continue;
        vis[u] = true;

        for (int i = head[u]; ~i; i = nx[i])
            if (dist1[ed[i]] > dist1[u] + wt[i])
                heap.emplace(dist1[ed[i]] = dist1[u] + wt[i], ed[i]);
    }
}

void Dijkstra2(int st, int delta) {
    memset(dist2, 0x3F, sizeof dist2);
    memset(vis, 0, sizeof vis);

    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.emplace(dist2[st] = 0, st);

    while (!heap.empty()) {
        auto [d, u] = heap.top();
        heap.pop();

        if (vis[u]) continue;
        vis[u] = true;

        for (int i = head[u]; ~i; i = nx[i]) {
            int v = ed[i];
            if (is_zero[i] && dist2[u] + wt[i] < dist1[v] + delta)
                wt[i] = wt[i ^ 1] = dist1[v] + delta - dist2[u];
            if (dist2[v] > dist2[u] + wt[i])
                heap.emplace(dist2[v] = dist2[u] + wt[i], v);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(head, -1, sizeof head);

    cin >> n >> m >> L >> s >> t;

    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;

        if (!w) {
            connect(u, v, 1, true);
            connect(v, u, 1, true);
        } else {
            connect(u, v, w, false);
            connect(v, u, w, false);
        }
    }

    Dijkstra1(s);

    if (dist1[t] > L || dist1[t] == INF)
        return puts("NO"), 0;

    int delta = L - dist1[t];

    Dijkstra2(s, delta);

    if (dist2[t] != L)
        return puts("NO"), 0;

    cout << "YES" << endl;
    for (int i = 0; i < idx; i += 2)
        cout << st[i] << ' ' << ed[i] << ' ' << wt[i] << endl;

    return fflush(stdout), 0;
}
