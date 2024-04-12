#include <bitset>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
using VI = vector<int>;

template <class Type>
struct Queue {
    vector<Type> e;
    int head, rear;
    void push(Type x) {
        e[++rear] = x;
    }
    Type extract() {
        return e[head++];
    }
    bool empty() {
        return head > rear;
    }
    Queue(int n) :
        head(0), rear(-1) {
        e.resize(n);
    }
};

const int N = 3e4 + 10;

VI G[N];
bitset<N> f[N];
int n, m, indeg[N];

VI topological_sort(int n) {
    Queue<int> q(n + 10);
    VI path;
    for (int i = 1; i <= n; i++)
        if (indeg[i] == 0)
            q.push(i);
    while (!q.empty()) {
        int t = q.extract();
        path.push_back(t);
        for (int ver : G[t]) {
            indeg[ver]--;
            if (indeg[ver] == 0)
                q.push(ver);
        }
    }
    return path;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        indeg[v]++;
    }

    VI ret = topological_sort(n);

    for (int i = ret.size() - 1; i >= 0; i--) {
        int u = ret[i];
        f[u][u] = 1;
        for (int ver : G[u])
            f[u] |= f[ver];
    }
    for (int i = 1; i <= n; i++)
        cout << f[i].count() << endl;
    return 0;
}
