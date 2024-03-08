#include <queue>
#include <vector>
#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;
using PII = pair<i64, int>;

const int N = 5e6 + 5;
const int M = 6e6 + 5;
const int INTMAX = (1LL << 31) - 1;

int n;
i64 l, r;
vector<int> a;
int ed[M], wt[M], nx[M], head[N], idx;
i64 dist[N];
bool vis[N];

void connect(int u, int v, int w) {
    ed[idx] = v;
    wt[idx] = w;
    nx[idx] = head[u];
    head[u] = idx++;
}

void Dijkstra(int st = 0) {
    memset(dist, 0x3F, sizeof dist);

    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.emplace(dist[st] = 0, st);

    while (!heap.empty()) {
        auto [d, u] = heap.top();
        heap.pop();

        if (vis[u]) continue;
        vis[u] = true;

        for (int i = head[u]; ~i; i = nx[i])
            if (dist[ed[i]] > dist[u] + wt[i])
                heap.emplace(dist[ed[i]] = dist[u] + wt[i], ed[i]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(head, -1, sizeof head);

    cin >> n >> l >> r;

    int min_a = INTMAX;
    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        if (x) {
            a.push_back(x);
            min_a = min(min_a, x);
        }
    }

    for (int i = 0; i < min_a; i++)
        for (int x : a)
            connect(i, (i + x) % min_a, x);

    Dijkstra();

    i64 ansl = 0, ansr = 0;
    for (int i = 0; i < min_a; i++) {
        if (r >= dist[i]) ansr += (r - dist[i]) / min_a + 1;
        if (l - 1 >= dist[i]) ansl += (l - 1 - dist[i]) / min_a + 1;
    }

    cout << ansr - ansl << endl;
    return fflush(stdout), 0;
}
