#include <vector>
#include <cstring>
#include <iostream>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using PII = pair<int, int>;

template <class T>
struct Queue {
    vector<T> data;
    int head, rear;
    void push(T x) {
        data[++rear] = x;
    }
    void pop() {
        head++;
    }
    T extract() {
        return data[head++];
    }
    T front() {
        return data[head];
    }
    T back() {
        return data[rear];
    }
    bool empty() {
        return head > rear;
    }
    void init(int n) {
        head = 0;
        rear = -1;
        data.clear();
        data.resize(n);
    }
    Queue() {}
    Queue(int n) {
        init(n);
    }
};

const int N = 2.5e4 + 10;
const int M = 1.5e5 + 10;
const int INF = 0x3F3F3F3F;

int n, m1, m2, start;
int head[N], dist[N], idx;
int ed[M], nx[M], wt[M];
bool vis[N];
vector<int> block[N];
int block_idx, belong[N];
int indeg[N];
Queue<int> q;

void connect(int u, int v, int w) {
    ed[idx] = v;
    wt[idx] = w;
    nx[idx] = head[u];
    head[u] = idx++;
}

// 深度优先搜索建立连通块
void DFS(int u) {
    block[block_idx].push_back(u);
    belong[u] = block_idx;

    for (int v = head[u]; ~v; v = nx[v]) {
        int j = ed[v];
        if (!belong[j]) // 避免因为双向边重复搜索造成无限递归
            DFS(j);
    }
}

void Dijkstra(int st) {
    __gnu_pbds::priority_queue<PII, greater<PII>> heap;

    // 将所有当前连通块内的点扔进堆中
    for (int u : block[st])
        heap.push({dist[u], u});

    while (!heap.empty()) {
        int u = heap.top().second;
        heap.pop();
        if (vis[u]) continue;
        vis[u] = true;

        for (int v = head[u]; ~v; v = nx[v]) {
            int j = ed[v];
            if (dist[j] > dist[u] + wt[v]) {
                dist[j] = dist[u] + wt[v];
                if (belong[j] == st) // 只更新连通块之内的
                    heap.push({dist[j], j});
            }

            // 更新连通块之间的拓扑图
            if (belong[j] != st) {
                indeg[belong[j]] -= 1;
                if (indeg[belong[j]] == 0)
                    q.push(belong[j]);
            }
        }
    }
}

void topological_sort(int st) {
    memset(dist, 0x3F, sizeof dist);
    dist[st] = 0;

    /*  由于每个连通块内的所有有向边均符合有向无环图
        所以连通块内部的点之间不可能存在负权边，否则就会出现环
        由于 Dijkstra 算法无法处理负权边
        所以使用可以处理负权边的拓扑排序进行预处理
        将 Dijkstra 应用于不存在负权边的每一个连通块内
        最终实现全局最短路的计算 */

    q.init(block_idx + 5); // 用队列记录连通块的拓扑序
    for (int i = 1; i <= block_idx; i++)
        if (indeg[i] == 0)
            q.push(i);

    while (!q.empty()) // 按照拓扑序
        Dijkstra(q.extract()); // 在当前连通块内求最短路
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(head, -1, sizeof head);

    cin >> n >> m1 >> m2 >> start;

    // 先只添加双向边
    while (m1--) {
        int u, v, w;
        cin >> u >> v >> w;
        connect(u, v, w);
        connect(v, u, w);
    }

    // 由双向边建立连通块
    for (int u = 1; u <= n; u++)
        if (!belong[u])
            block_idx += 1, DFS(u);

    // 在连通块之间建立有向边
    while (m2--) {
        int u, v, w;
        cin >> u >> v >> w;
        connect(u, v, w);
        indeg[belong[v]] += 1;
    }

    // 找到拓扑序并按照拓扑序进行最短路
    topological_sort(start);

    for (int i = 1; i <= n; i++)
        if (dist[i] > INF / 2) cout << "NO PATH" << endl;
        else cout << dist[i] << endl;

    return 0;
}
