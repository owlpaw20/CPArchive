#include <stack>
#include <cstdio>
#include <cstring>

#define endl '\n'

namespace FastIO {
    int read() {
        int x = 0, f = 1;
        char ch = getchar();
        while (ch < '0' || ch > '9') {
            if (ch == '-')
                f = -f;
            ch = getchar();
        }
        while (ch >= '0' && ch <= '9')
            x = x * 10 + ch - 48, ch = getchar();
        return x * f;
    }
    void write(int x) {
        if (x < 0) putchar('-'), x = -x;
        if (x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
}  // namespace FastIO
using namespace FastIO;

const int N = 5e3 + 10;
const int M = 2e4 + 10;

int n, m;
int head[N], ed[M], nx[M], idx;
int dfn[N], low[N], dcc[N];
int dcc_cnt, timestamp;
bool is_bridge[M];
std::stack<int> stk;
int deg[N];

void connect(int u, int v) {
    ed[idx] = v;
    nx[idx] = head[u];
    head[u] = idx++;
}

void Tarjan(int u, int from = -1) {
    dfn[u] = low[u] = ++timestamp;

    stk.push(u);

    for (int i = head[u]; ~i; i = nx[i]) {
        int v = ed[i];
        if (!dfn[v]) {
            Tarjan(v, i);
            low[u] = std::min(low[u], low[v]);
            if (dfn[u] < low[v])
                is_bridge[i] = is_bridge[i ^ 1] = true;
        } else if (i != (from ^ 1))
            low[u] = std::min(low[u], dfn[v]);
    }

    if (dfn[u] == low[u]) {
        dcc_cnt++;
        int v;
        do {
            v = stk.top();
            stk.pop();
            dcc[v] = dcc_cnt;
        } while (v != u);
    }
}

int main() {
    memset(head, -1, sizeof head);

    n = read(), m = read();
    while (m--) {
        int u, v;
        u = read(), v = read();
        connect(u, v);
        connect(v, u);
    }

    Tarjan(1);

    for (int i = 0; i < idx; i++)
        deg[dcc[ed[i]]] += is_bridge[i];

    int ans = 0;
    for (int i = 1; i <= dcc_cnt; i++)
        if (deg[i] == 1)
            ans++;

    write((ans + 1) / 2), putchar('\n');
    fflush(stdout);
    return 0;
}
