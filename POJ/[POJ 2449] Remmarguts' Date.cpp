/* 用 A* 算法解决 K 短路问题，是通过为搜索到的当前状态定义一个
 * 估价函数 f(x) = g(x) + h(x)，其中 g(x) 为从起点到当前状
 * 态的实际代价，而 h(x) 为当前状态到达目标状态的估计代价。每次
 * 取出 f(x) 的最优状态 x，扩展其所有子状态，得到结果。因此 A*
 * 算法是基于优先队列的。
 *
 * 在求解 k 短路问题时，令 h(x) 为从当前结点到达终点 t 的最短
 * 路径长度。可以通过在反向图上对结点 t 跑单源最短路预处理出对
 * 每个结点的估计代价。*/

#include <queue>
#include <tuple>
#include <cstring>
#include <iostream>
#define endl '\n'

using namespace std;
using PII = pair<int, int>;
using TIII = tuple<int, int, int>;

const int N = 1e3 + 10;
const int M = 2e4 + 10;

int n, m, S, T, K;
int head[N], rhead[N], idx;
int ed[M], nx[M], wt[M], dist[N], Rank[N];
bool vis[N];

void connect(int u, int v, int w, int* head) {
    ed[idx] = v;
    wt[idx] = w;
    nx[idx] = head[u];
    head[u] = idx++;
}

void Dijkstra(int st, int* head) {
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    memset(dist, 0x3F, sizeof dist);
    heap.emplace(dist[st] = 0, st);

    while (!heap.empty()) {
        int u = heap.top().second;
        heap.pop();

        if (vis[u]) continue;
        vis[u] = true;

        for (int i = head[u]; ~i; i = nx[i])
            if (dist[ed[i]] > dist[u] + wt[i])
                heap.emplace(dist[ed[i]] = dist[u] + wt[i], ed[i]);
    }
}

int BFS(int st) {
    priority_queue<TIII, vector<TIII>, greater<TIII>> heap;
    heap.emplace(dist[st], 0, st);

    while (!heap.empty()) {
        auto [eval, d, u] = heap.top();
        heap.pop();

        Rank[u] += 1;
        if (Rank[T] == K)
            return d;

        for (int i = head[u]; ~i; i = nx[i])
            if (Rank[ed[i]] < K)
                heap.emplace(d + wt[i] + dist[ed[i]], d + wt[i], ed[i]);
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(head, -1, sizeof head);
    memset(rhead, -1, sizeof rhead);

    cin >> n >> m;
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        connect(u, v, w, head);
        connect(v, u, w, rhead);
    }
    cin >> S >> T >> K;

    if (S == T) K += 1;

    Dijkstra(T, rhead);
    cout << BFS(S) << endl;

    fflush(stdout);
    return 0;
}
