#include <vector>
#include <iostream>
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

const int N = 1e2 + 10;

int n, t, indeg[N];
VI g[N];

VI topological_sort(int n) {
    Queue<int> q(n + 10);
    VI path;
    for (int i = 1; i <= n; i++)
        if (indeg[i] == 0)
            q.push(i);
    while (!q.empty()) {
        int t = q.extract();
        path.push_back(t);
        for (int ver : g[t]) {
            indeg[ver]--;
            if (indeg[ver] == 0)
                q.push(ver);
        }
    }
    return path;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        while (cin >> t && t)
            g[i].push_back(t), indeg[t]++;
    VI ret = topological_sort(n);
    for (int i : ret) cout << i << ' ';
    cout << endl;
    return 0;
}
