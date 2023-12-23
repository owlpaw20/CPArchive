#include <vector>
#include <iostream>
using namespace std;
using VI = vector<int>;

template <class Type>
struct Queue {
    vector<Type> e;
    int head, rear;
    void push(Type x) { e[++rear] = x; }
    Type extract() { return e[head++]; }
    bool empty() { return head > rear; }
    Queue(int n) : head(0), rear(-1) { e.resize(n); }
};

const int N = 1e4 + 10;

VI G[N];
int n, m;
int indeg[N], pay[N];

VI topological_sort(int n) {
    VI path;
    Queue<int> q(n + 10);
    for (int i = 1; i <= n; i++)
        if (indeg[i] == 0)
            q.push(i), pay[i] = 100;
    while (!q.empty()) {
        int t = q.extract();
        path.push_back(t);
        for (int ver : G[t]) {
            indeg[ver]--;
            if (indeg[ver] == 0)
                q.push(ver), pay[ver] = pay[t] + 1;
        }
    }
    return path;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> m;
    while (m--) {
        int a, b;
        cin >> a >> b;
        G[b].push_back(a);
        indeg[a]++;
    }
    VI ret = topological_sort(n);
    if (ret.size() < n) return 0 & puts("Poor Xed");
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans += pay[i];
    cout << ans << endl;
    return 0;
}
