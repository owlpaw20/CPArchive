#include <stack>
#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e4 + 10;
const int M = 5e4 + 10;

int n, m;
int head[N], ed[M], nx[M], idx;
int dfn[N], low[N], timestamp;
bool in_stk[N];
int belong[N], scc_cnt, sizes[N];
int out[N];
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
        int j = ed[i];
        if (!dfn[j]) {
            Tarjan(j);
            low[u] = min(low[u], low[j]);
        } else if (in_stk[j])
            low[u] = min(low[u], dfn[j]);
    }

    if (dfn[u] == low[u]) {
        scc_cnt++;
        int y;
        do {
            y = stk.top();
            stk.pop();
            in_stk[y] = false;
            belong[y] = scc_cnt;
            sizes[scc_cnt]++;
        } while (y != u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(head, -1, sizeof head);

    cin >> n >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        connect(u, v);
    }

    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0)
            Tarjan(i);

    for (int i = 1; i <= n; i++)
        for (int j = head[i]; ~j; j = nx[j]) {
            int u = belong[i];
            int v = belong[ed[j]];
            if (u != v) out[u]++;
        }

    int zero = 0, sum = 0;
    for (int i = 1; i <= scc_cnt; i++)
        if (!out[i]) {
            zero++;
            sum += sizes[i];
            if (zero > 1) {
                sum = 0;
                break;
            }
        }

    cout << sum << endl;
    fflush(stdout);
    return 0;
}
