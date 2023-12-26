#include <queue>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;

const int N = 1000;
struct Vertex {
    int ed, nx;
};

int n, t;
int idx, h[N], to[N];
Vertex edges[N];
queue<int> q;
vector<int> topo;

void add_edge(int u, int v) {
    edges[idx].ed = v;
    edges[idx].nx = h[u];
    h[u] = idx;
    idx++;
}

void toposort() {
    for (int i = 1; i <= n; i++)
        if (!to[i])
            q.push(i);
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        topo.push_back(t);
        for (int i = h[t]; ~i; i = edges[i].nx) {
            int j = edges[i].ed;
            to[j]--;
            if (!to[j]) q.push(j);
        }
    }
    for (auto i : topo)
        cout << i << " ";
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i++)
        while (cin >> t) {
            if (!t) break;
            add_edge(i, t);
            to[t]++;
        }
    toposort();
    return 0;
}
