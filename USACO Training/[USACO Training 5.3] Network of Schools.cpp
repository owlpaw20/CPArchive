#include <stack>
#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e2 + 10;
const int M = 1e4 + 10;

int n;
int ed[M], nx[M], head[N], idx;
int dfn[N], low[N], timestamp;
bool in_stk[N];
int belong[N], sizes[N], scc_cnt;
int indeg[N], outdeg[N];
stack<int> stk;

void connect(int u, int v) {
    ed[idx] = v;
    nx[idx] = head[u];
    head[u] = idx++;
}

void Tarjan(int u) {
    dfn[u] = low[u] = ++timestamp;

    stk.push(u);
    in_stk[u] = true;

    for (int i = head[u]; ~i; i = nx[i]) {
        int v = ed[i];
        if (!dfn[v]) {
            Tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (in_stk[v])
            low[u] = min(low[u], dfn[v]);
    }

    if (low[u] == dfn[u]) {
        scc_cnt++;
        int v;
        do {
            v = stk.top();
            stk.pop();
            in_stk[v] = false;
            belong[v] = scc_cnt;
            sizes[scc_cnt]++;
        } while (v != u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(head, -1, sizeof head);

    cin >> n;
    for (int i = 1, t; i <= n; i++)
        while (cin >> t, t)
            connect(i, t);

    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            Tarjan(i);

    for (int i = 1; i <= n; i++)
        for (int j = head[i]; ~j; j = nx[j]) {
            int u = belong[i];
            int v = belong[ed[j]];
            if (u != v)
                outdeg[u]++, indeg[v]++;
        }

    int root = 0, leaf = 0;
    for (int i = 1; i <= scc_cnt; i++) {
        if (indeg[i] == 0) root++;
        if (outdeg[i] == 0) leaf++;
    }

    cout << root << endl;
    if (scc_cnt == 1) cout << 0 << endl;
    else cout << max(root, leaf) << endl;

    fflush(stdout);
    return 0;
}
