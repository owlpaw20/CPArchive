#include <queue>
#include <cstdio>
#include <vector>
#include <climits>
#include <cstring>
using namespace std;

typedef pair<int, int> PII;
const int N = 1e5 + 10;
const int M = 2e5 + 10;

int n, m, s, u, v, w, idx;
int ed[M], nx[M], wt[M], head[N], dist[N];
bool vis[N];

inline void add_edge(int u, int v, int w) {
    ed[idx] = v;
    wt[idx] = w;
    nx[idx] = head[u];
    head[u] = idx++;
}

void Dijkstra() {
    for (int i = 1; i <= n; i++)
        dist[i] = INT_MAX;
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
}

int main() {
    scanf("%d %d %d", &n, &m, &s);
    memset(head, -1, sizeof head);
    while (m--) {
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
    }
    Dijkstra();
    for (int i = 1; i <= n; i++)
        printf("%d ", dist[i]);
    printf("\n");
    return 0;
}
