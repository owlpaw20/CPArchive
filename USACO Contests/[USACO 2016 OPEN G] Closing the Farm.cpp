#include <cstring>
#include <numeric>
#include <iostream>
#define endl '\n'

using namespace std;

const int N = 2e5 + 10;
const int M = 4e5 + 10;

struct DisjointSet {
    int p[N];
    void init(int n) {
        memset(p, 0, sizeof p);
        iota(p + 1, p + n + 1, 1);
    }
    int find(int x) {
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }
    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        return p[x] = y, true;
    }
};

int n, m, idx, close[N];
int ed[M], nx[M], head[N];
bool vis[N], ans[N];
DisjointSet DSU;

void connect(int u, int v) {
    ed[idx] = v;
    nx[idx] = head[u];
    head[u] = idx++;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(head, -1, sizeof head);

    cin >> n >> m;

    int u, v;
    while (m--) {
        cin >> u >> v;
        connect(u, v);
        connect(v, u);
    }

    for (int i = 1; i <= n; i++)
        cin >> close[i];

    DSU.init(n);
    vis[close[n]] = true;  // 最后一个关闭的农场视为第一个被打开
    ans[n] = true;         // 最后一个农场开启后显然一定联通，所以成立

    int cnt = 0;
    for (int i = n - 1; i > 0; i--) {  // 倒序关闭农场等价于正序开启农场
        vis[close[i]] = true;          // 当前农场被开启
        for (int j = head[close[i]]; ~j; j = nx[j]) {
            int u = close[i], v = ed[j];
            if (vis[v] && DSU.merge(u, v))  // 如果有终点的农场也开启
                cnt += 1;                   // 就合并
        }
        if (cnt == n - i)
            ans[i] = true;  // 如果当前开放的所有农场都已联通则存储答案
        else
            ans[i] = false;
    }

    for (int i = 1; i <= n; i++)
        puts(ans[i] ? "YES" : "NO");

    fflush(stdout);
    return 0;
}
