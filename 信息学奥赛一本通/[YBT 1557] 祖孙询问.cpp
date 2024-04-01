#include <vector>
#include <cstring>
#include <iostream>
#define endl '\n'
using namespace std;

const int N = 4e4 + 10;
const int M = 8e4 + 10;

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

int n, m, root, idx;
int anc[N][20], depth[N];
int ed[M], nx[M], head[M];

int log2(int x) {
    int exp = 0;
    while (x >>= 1)
        exp += 1;
    return exp;
}

void connect(int u, int v) {
    ed[idx] = v;
    nx[idx] = head[u];
    head[u] = idx++;
}

void BFS(int root) {
    Queue<int> q(N);
    q.push(root);
    depth[root] = 1;
    while (!q.empty()) {
        int u = q.extract();
        for (int i = head[u]; ~i; i = nx[i]) {
            int v = ed[i];
            if (depth[v]) continue;
            depth[v] = depth[u] + 1;
            anc[v][0] = u;
            for (int i = 1; i <= log2(n); i++)
                anc[v][i] = anc[anc[v][i - 1]][i - 1];
            q.push(v);
        }
    }
}

int LCA(int u, int v) {
    if (depth[u] > depth[v]) swap(u, v);
    for (int i = log2(n); i >= 0; i--)
        if (depth[anc[v][i]] >= depth[u])
            v = anc[v][i];
    if (u == v) return u;
    for (int i = log2(n); i >= 0; i--)
        if (anc[v][i] != anc[u][i])
            u = anc[u][i], v = anc[v][i];
    return anc[u][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(head, -1, sizeof head);

    cin >> n;
    for (int i = 1, u, v; i <= n; i++) {
        cin >> u >> v;
        if (v == -1)
            root = u;
        else {
            connect(u, v);
            connect(v, u);
        }
    }

    BFS(root);

    cin >> m;
    int u, v;
    while (m--) {
        cin >> u >> v;
        int t = LCA(u, v);
        if (t == u)
            cout << 1 << endl;
        else if (t == v)
            cout << 2 << endl;
        else
            cout << 0 << endl;
    }

    fflush(stdout);
    return 0;
}
