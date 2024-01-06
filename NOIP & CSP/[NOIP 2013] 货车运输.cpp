#include <queue>
#include <tuple>
#include <vector>
#include <climits>
#include <cstring>
#include <numeric>
#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;
using TPL = tuple<int, int, int>;

const int N = 1e4 + 10;
const int M = 1e5 + 10;

int n, m;

namespace LCA {
    int ed[M], nx[M], wt[M], head[N], idx;
    int dpt[N], fa[N][20], maxw[N][20];
    bool vis[N];

    int log2(int x) {
        int exp = 0;
        while (x >>= 1)
            exp += 1;
        return exp;
    }

    void connect(int u, int v, int w) {
        ed[idx] = v;
        wt[idx] = w;
        nx[idx] = head[u];
        head[u] = idx++;
    }

    void BFS(int root) {
        queue<int> q;
        q.push(root);
        dpt[root] = 1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            if (vis[u]) continue;
            vis[u] = true;

            for (int i = head[u]; ~i; i = nx[i]) {
                int v = ed[i], w = wt[i];
                if (dpt[v] || vis[v]) continue;

                dpt[v] = dpt[u] + 1;
                fa[v][0] = u, maxw[v][0] = w;
                for (int j = 1; j <= log2(n); j++) {
                    fa[v][j] = fa[fa[v][j - 1]][j - 1];
                    maxw[v][j] = min(maxw[v][j - 1], maxw[fa[v][j - 1]][j - 1]);
                }

                q.push(v);
            }
        }
    }

    void init() {
        for (int i = 1; i <= n; i++)
            if (!vis[i]) BFS(i);
    }

    int query(int u, int v) {
        if (dpt[u] > dpt[v]) swap(u, v);

        int ret = INT_MAX;

        for (int i = log2(n); i >= 0; i--)
            if (dpt[fa[v][i]] >= dpt[u])
                ret = min(ret, maxw[v][i]), v = fa[v][i];

        if (u == v) return ret;

        for (int i = log2(n); i >= 0; i--)
            if (fa[v][i] != fa[u][i])
                ret = min({ret, maxw[v][i], maxw[u][i]}), u = fa[u][i], v = fa[v][i];

        return min({ret, maxw[v][0], maxw[u][0]});
    }
}  // namespace LCA

namespace MST {
    vector<TPL> edges;
    int fa[N];

    int find(int x) {
        if (fa[x] == x) return x;
        return fa[x] = find(fa[x]);
    }

    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        return fa[x] = y, true;
    }

    void Kruskal() {
        sort(edges.begin(), edges.end(), greater<TPL>());
        for (auto [w, u, v] : edges)
            if (merge(u, v))
                LCA::connect(u, v, w), LCA::connect(v, u, w);
    }
}  // namespace MST
using namespace MST;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(LCA::head, -1, sizeof LCA::head);

    cin >> n >> m;
    iota(fa + 1, fa + n + 1, 1);

    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.emplace_back(w, u, v);
        edges.emplace_back(w, v, u);
    }

    Kruskal();
    LCA::init();

    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        if (find(u) != find(v)) cout << -1 << endl;
        else cout << LCA::query(u, v) << endl;
    }

    fflush(stdout);
    return 0;
}
