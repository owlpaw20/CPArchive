/*  最短路最短的最短路，一定连接了特殊点之间的某两个不同的点，
    则这两个点的编号一定至少有一位二进制位不同。
    每次循环根据某一位二进制位为 0 或 1 将所有的特殊点分成两组，
    并借助虚拟源点求出这两组特殊点之间的最短的最短路。
    由于这两个点一定有一个二进制位不同，
    所以一定会在上述的某一次循环中被分为不同组，
    因此最终取每次循环计算最短路结果的最小值，即为答案。 */

#include <queue>
#include <vector>
#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;
using PII = pair<i64, int>;

const int N = 1e5 + 5;

int n, m, K;
int city[N];
i64 dist[N];
bool vis[N];
vector<vector<PII>> graph;

void input() {
    cin >> n >> m >> K;
    memset(city, 0, sizeof city);
    graph.assign(n + 3, vector<PII>());

    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
    }

    for (int i = 1; i <= K; i++) cin >> city[i];
}

i64 Dijkstra(int st, int fn) {
    memset(vis, 0, sizeof vis);
    memset(dist, 0x3F, sizeof dist);

    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.emplace(dist[st] = 0, st);

    while (!heap.empty()) {
        auto [d, u] = heap.top();
        heap.pop();

        if (vis[u]) continue;
        vis[u] = true;

        for (auto [v, w] : graph[u])
            if (dist[v] > dist[u] + w)
                heap.emplace(dist[v] = dist[u] + w, v);
    }

    return dist[fn];
}

void solve() {
    i64 ans = (1ULL << 63) - 1;

    vector<vector<PII>> tmp(graph);
    int va = n + 1, vb = n + 2; // 建立两组节点的虚拟源点

    for (int i = 0; (1 << i) <= K; i++) { // 枚举第 i 个二进制位
        for (int j = 1; j <= K; j++) // 对于所有的城市
            if ((1 << i) & j) // 如果二进制位为 1 则进入 A 组
                graph[va].emplace_back(city[j], 0);
            else // 否则进入 B 组
                graph[city[j]].emplace_back(vb, 0); // 这里只连一条有向边即可

        ans = min(ans, Dijkstra(va, vb)); // 更新整体最短路
        graph = tmp;

        // 由于是有向图，所以还要倒着做一遍
        for (int j = 1; j <= K; j++)
            if ((1 << i) & j) graph[city[j]].emplace_back(vb, 0);
            else graph[va].emplace_back(city[j], 0);

        ans = min(ans, Dijkstra(va, vb));
        graph = tmp;
    }

    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) input(), solve();

    return fflush(stdout), 0;
}
