#include <string>
#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e5 + 5;
const int M = 2e5 + 5;

struct SegTree {
    struct {
        int l, r, len;
        int sum, alt;
    } node[N << 2];

    void maintain(int u) { node[u].sum = node[u << 1].sum + node[u << 1 | 1].sum; }

    void propagate(int u) {
        auto& root = node[u];
        auto& left = node[u << 1];
        auto& right = node[u << 1 | 1];

        if (root.alt != -1) {
            left.alt = root.alt;
            left.sum = root.alt * left.len;
            right.alt = root.alt;
            right.sum = root.alt * right.len;
            root.alt = -1;
        }
    }

    void build(int u, int l, int r) {
        node[u].l = l;
        node[u].r = r;
        node[u].alt = -1;
        node[u].len = r - l + 1;

        if (l == r)
            return (void)(node[u].sum = 0);

        int mid = (l + r) >> 1;

        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);

        // maintain(u);
    }

    void overwrite(int u, int l, int r, bool x) {
        int nl = node[u].l, nr = node[u].r;

        if (nl >= l && nr <= r) {
            node[u].alt = x;
            node[u].sum = x * node[u].len;
            return;
        }

        propagate(u);

        int mid = (nl + nr) >> 1;

        if (l <= mid) overwrite(u << 1, l, r, x);
        if (r > mid) overwrite(u << 1 | 1, l, r, x);

        maintain(u);
    }

    int query(int u, int l, int r) {
        int nl = node[u].l, nr = node[u].r;

        if (nl >= l && nr <= r)
            return node[u].sum;

        propagate(u);

        int mid = (nl + nr) >> 1;
        int ret = 0;

        if (l <= mid) ret += query(u << 1, l, r);
        if (r > mid) ret += query(u << 1 | 1, l, r);

        return ret;
    }
} SGT;

namespace Decomp {
    int ed[M], nx[M], val[N], head[N], idx;
    int fa[N], pref[N], depth[N], size[N], top[N];
    int dfn[N], new_val[N], timestamp;

    void connect(int u, int v) {
        ed[idx] = v;
        nx[idx] = head[u];
        head[u] = idx++;
    }

    void DFS1(int u, int f) {
        fa[u] = f;
        size[u] = 1;
        depth[u] = depth[f] + 1;

        for (int i = head[u]; ~i; i = nx[i]) {
            int v = ed[i];
            if (v == f) continue;

            DFS1(v, u);
            size[u] += size[v];

            if (!pref[u] || size[pref[u]] < size[v])
                pref[u] = v;
        }
    }

    void DFS2(int u, int path_top) {
        top[u] = path_top;
        dfn[u] = ++timestamp;
        new_val[timestamp] = val[u];

        if (!pref[u]) return;

        DFS2(pref[u], path_top);
        for (int i = head[u]; ~i; i = nx[i])
            if (ed[i] != fa[u] && ed[i] != pref[u])
                DFS2(ed[i], ed[i]);
    }

    void update_path_val(int u, int v, bool flag = true) {
        while (top[u] != top[v]) {
            if (depth[top[u]] < depth[top[v]]) swap(u, v);
            SGT.overwrite(1, dfn[top[u]], dfn[u], flag);
            u = fa[top[u]];
        }

        if (depth[u] > depth[v]) swap(u, v);
        SGT.overwrite(1, dfn[u], dfn[v], flag);
    }

    void update_subtree_val(int u, bool v = false) { SGT.overwrite(1, dfn[u], dfn[u] + size[u] - 1, v); }
    int query_subtree_sum(int u) { return SGT.query(1, dfn[u], dfn[u] + size[u] - 1); }
}  // namespace Decomp

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(Decomp::head, -1, sizeof Decomp::head);

    int n;
    cin >> n;
    SGT.build(1, 1, n);

    for (int i = 2, x; i <= n; i++) {
        cin >> x, x++;
        Decomp::connect(i, x);
        Decomp::connect(x, i);
    }

    Decomp::DFS1(1, 0);
    Decomp::DFS2(1, 1);

    int m;
    cin >> m;
    while (m--) {
        string type;
        int x;

        cin >> type >> x, x++;

        int ans1 = Decomp::query_subtree_sum(1);
        if (type == "install") Decomp::update_path_val(1, x);
        else Decomp::update_subtree_val(x);
        int ans2 = Decomp::query_subtree_sum(1);

        cout << abs(ans1 - ans2) << endl;
    }

    return fflush(stdout), 0;
}
