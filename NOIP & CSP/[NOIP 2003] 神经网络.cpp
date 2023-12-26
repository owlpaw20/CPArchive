#include <queue>
#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e2 + 5;
const int M = 1e4 + 5;

int n, m;
int c[N], u[N];

int head[N], idx;
int ed[M], nx[M], wt[M];
int indeg[N], outdeg[N];

void connect(int u, int v, int w) {
    ed[idx] = v;
    wt[idx] = w;
    nx[idx] = head[u];
    head[u] = idx++;
}

void topological_sort() {
    queue<int> q;

    for (int i = 1; i <= n; i++)
        if (c[i] > 0 && indeg[i] == 0)
            q.push(i);

    while (!q.empty()) {
        int uu = q.front();
        q.pop();

        for (int i = head[uu]; ~i; i = nx[i]) {
            int v = ed[i];
            indeg[v]--;

            if (c[uu] > 0)
                c[v] += wt[i] * c[uu];

            if (indeg[v] == 0) {
                q.push(v);
                c[v] -= u[v];
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(head, -1, sizeof head);

    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        cin >> c[i] >> u[i];

    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        connect(u, v, w);
        indeg[v]++, outdeg[u]++;
    }

    topological_sort();

    bool flag = false;
    for (int i = 1; i <= n; i++)
        if (outdeg[i] == 0 && c[i] > 0)
            cout << i << ' ' << c[i] << endl, flag = true;

    if (!flag) puts("NULL");
    fflush(stdout);
    return 0;
}
