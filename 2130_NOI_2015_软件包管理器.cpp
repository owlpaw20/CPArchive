#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e5 + 5;
const int M = 2e5 + 5;

namespace Decomp {
    int ed[M], nx[M], head[N], idx;
    int fa[N], size[N], depth[N], pref[N];
    int dfn[N], top[N], nidx;

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

            if (!pref[u] || size[pref[u]] < size[v]) pref[u] = v;
        }
    }

    void DFS2(int u, int pt) {
        top[u] = pt;
        dfn[u] = ++nidx;

        if (!pref[u]) return;

        for (int i = head[u]; ~i; i = nx[i])
            if (ed[i] != fa[u] && ed[i] != pref[u])
                DFS2(ed[i], ed[i]);
    }
}  // namespace Decomp

int n, q;

struct SegTree {
    struct Node {
        int l, r;
        int alt, sum;
    } node[N << 2];

    void maintain(int u) { node[u].sum = node[u << 1].sum + node[u << 1 | 1].sum; }

    void propagate(int u) {
        Node& root = node[u];
        Node& left = node[u << 1];
        Node& right = node[u << 1 | 1];

        if (root.alt != -1) {
            left.alt = root.alt;
            right.alt = root.alt;
            left.sum = root.alt * (left.r - left.l + 1);
            right.sum = root.alt * (right.r - right.l + 1);

            root.alt = -1;
        }
    }

    void build(int u, int l, int r) {
        node[u].l = l;
        node[u].r = r;
        node[u].alt = -1;

        if (l == r)
            return (void)(node[u].sum = 0);

        int mid = (l + r) >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);

        maintain(u);
    }

    void flatten(int u, int l, int r, bool flag) {
        int nl = node[u].l, nr = node[u].r;
        if (nl >= l && nr <= r) {
            node[u].alt = flag;
            node[u].sum = flag * (nr - nl + 1);
            return;
        }

        propagate(u);

        int mid = (nl + nr) >> 1;
        if (l <= mid) flatten(u << 1, l, r, flag);
        if (r > mid) flatten(u << 1 | 1, l, r, flag);

        maintain(u);
    }

    int query_sum(int u, int l, int r) {
        int nl = node[u].l, nr = node[u].r;
        if (nl >= l && nr <= r)
            return node[u].sum;

        propagate(u);

        int mid = (nl + nr) >> 1, ret = 0;
        if (l <= mid) ret += query_sum(u << 1, l, r);
        if (r > mid) ret += query_sum(u << 1 | 1, l, r);

        return ret;
    }
} SGT;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(Decomp::head, -1, sizeof Decomp::head);

    cin >> n >> q;

    for (int i = 2, j; i <= n; i++) {
        cin >> j, j++;
        Decomp::connect(i, j);
        Decomp::connect(j, i);
    }

    Decomp::DFS1(1, 0);
    Decomp::DFS2(1, 1);

    SGT.build(1, 1, n);

    return fflush(stdout), 0;
}
