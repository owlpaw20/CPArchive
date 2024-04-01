#include <vector>
#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;

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

const int N = 4e4 + 5;
const int M = 8e4 + 5;

int T, idx, n, m;
int ed[M], nx[M], wt[M], head[N];
int anc[N][16], depth[N], dist[N];
Queue<int> q;

void graph_reset() {
    memset(ed, 0, sizeof ed);
    memset(nx, 0, sizeof nx);
    memset(wt, 0, sizeof wt);
    memset(head, -1, sizeof head);
    memset(depth, 0, sizeof depth);
    q.init(N);
    idx = 0;
}

int log2(int x) {
    int exp = 0;
    while (x >>= 1)
        exp += 1;
    return exp;
}

void connect(int u, int v, int w) {
    ed[idx] = v;
    wt[idx] = w;
    nx[idx] = head[u];
    head[u] = idx++;
}

// 预处理出各节点的所有祖先节点
void BFS() {
    q.push(1);
    depth[1] = 1;

    while (!q.empty()) {
        int u = q.extract(); // 取出当前遍历到的子树的根节点 U
        for (int i = head[u]; ~i; i = nx[i]) { // 遍历 U 的所有子节点
            int v = ed[i];
            if (depth[v]) continue;

            depth[v] = depth[u] + 1; // 保存当前节点的深度
            dist[v] = dist[u] + wt[i]; // 保存当前节点对根节点的距离

            anc[v][0] = u; // 节点 V 的父节点为 U
            for (int j = 1; j <= log2(n); j++) // 递推地预处理出 V 的所有祖先节点
                anc[v][j] = anc[anc[v][j - 1]][j - 1];

            q.push(v);
        }
    }
}

// 获取某两个节点的最近公共祖先到根节点的距离
int query_LCA(int u, int v) {
    if (depth[u] > depth[v]) swap(u, v);

    // 将 V 向上移动到 U 同深度的位置
    for (int i = log2(n); i >= 0; i--)
        if (depth[anc[v][i]] >= depth[u])
            v = anc[v][i];

    if (u == v) // 如果 U 就是 V 的祖先
        return u; // 那么直接返回即可

    // 将 U 和 V 同时向上移动，直到二者移动到同一节点的子节点处
    for (int i = log2(n); i >= 0; i--)
        if (anc[v][i] != anc[u][i])
            u = anc[u][i], v = anc[v][i];
    return anc[u][0]; // 即可找到最近公共祖先
}

void solve() {
    graph_reset();

    cin >> n >> m;
    for (int i = 1, u, v, w; i < n; i++) {
        cin >> u >> v >> w;
        connect(u, v, w);
        connect(v, u, w);
    }

    BFS(); // 预处理祖先节点

    while (m--) {
        int u, v;
        cin >> u >> v;
        cout << dist[u] + dist[v] - 2 * dist[query_LCA(u, v)] << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) solve();

    fflush(stdout);
    return 0;
}
