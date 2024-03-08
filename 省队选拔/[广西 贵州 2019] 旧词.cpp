// 前置题目：辽宁省选 2014 "LCA"

#include <tuple>
#include <vector>
#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;
using i64 = long long;
using TUP = tuple<int, int, int>;

const int N = 5e4 + 5;
const int MOD = 998244353;

int n;
int powers[N];
vector<TUP> queries;
int answers[N];

namespace TD {
    vector<int> graph[N];
    int fa[N], size[N], depth[N], pref[N];
    int dfn[N], top[N], new_val[N], timestamp;

    void DFS1(int u, int f = 0) {
        fa[u] = f;
        size[u] = 1;
        depth[u] = depth[f] + 1;

        for (int v : graph[u]) {
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
        new_val[timestamp] = powers[u];

        if (!pref[u]) return;

        DFS2(pref[u], path_top);
        for (int v : graph[u])
            if (v != fa[u] && v != pref[u])
                DFS2(v, v);
    }

    struct SegTree {
        struct {
            int l, r;
            int sum, val, tag;
        } node[N << 2];

        void pushup(int u) {
            node[u].sum = (node[u << 1].sum + node[u << 1 | 1].sum) % MOD;
        }

        void pushdown(int u) {
            auto& fa = node[u];
            auto& lc = node[u << 1];
            auto& rc = node[u << 1 | 1];

            if (fa.tag) {
                lc.tag = (lc.tag + fa.tag) % MOD;
                rc.tag = (rc.tag + fa.tag) % MOD;
                lc.sum = (lc.sum + (i64)lc.val * fa.tag % MOD) % MOD;
                rc.sum = (rc.sum + (i64)rc.val * fa.tag % MOD) % MOD;
                fa.tag = 0;
            }
        }

        void build(int u = 1, int l = 1, int r = n) {
            node[u].l = l;
            node[u].r = r;
            node[u].tag = 0;

            if (l == r)
                return (void)(node[u].val = new_val[l]);

            int mid = (l + r) >> 1;

            build(u << 1, l, mid);
            build(u << 1 | 1, mid + 1, r);

            node[u].val = (node[u << 1].val + node[u << 1 | 1].val) % MOD;
        }

        void update(int u, int l, int r) {
            int nl = node[u].l, nr = node[u].r;

            if (nl >= l && nr <= r) {
                node[u].tag = (node[u].tag + 1) % MOD;
                node[u].sum = (node[u].sum + node[u].val) % MOD;
                return;
            }

            pushdown(u);

            int mid = (nl + nr) >> 1;

            if (l <= mid) update(u << 1, l, r);
            if (r > mid) update(u << 1 | 1, l, r);

            pushup(u);
        }

        int query(int u, int l, int r) {
            int nl = node[u].l, nr = node[u].r;

            if (nl >= l && nr <= r)
                return node[u].sum;

            pushdown(u);

            int mid = (nl + nr) >> 1;
            int ret = 0;

            if (l <= mid) ret = (ret + query(u << 1, l, r)) % MOD;
            if (r > mid) ret = (ret + query(u << 1 | 1, l, r)) % MOD;

            return ret;
        }
    } SGT;

    void update_val_on_path(int u, int v) {
        while (top[u] != top[v]) {
            if (depth[top[u]] < depth[top[v]]) swap(u, v);
            SGT.update(1, dfn[top[u]], dfn[u]);
            u = fa[top[u]];
        }

        if (depth[u] > depth[v]) swap(u, v);
        SGT.update(1, dfn[u], dfn[v]);
    }

    int query_sum_of_path(int u, int v) {
        int ret = 0;

        while (top[u] != top[v]) {
            if (depth[top[u]] < depth[top[v]]) swap(u, v);
            ret = (ret + SGT.query(1, dfn[top[u]], dfn[u])) % MOD;
            u = fa[top[u]];
        }

        if (depth[u] > depth[v]) swap(u, v);
        ret = (ret + SGT.query(1, dfn[u], dfn[v])) % MOD;
        return ret;
    }
}  // namespace TD

int power(int b, int e, int p = MOD) {
    int ret = 1;
    while (e) {
        if (e & 1) ret = (i64)ret * b % p;
        b = (i64)b * b % p;
        e >>= 1;
    }
    return ret % p;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q, k;
    cin >> n >> q >> k;

    for (int i = 2, v; i <= n; i++) {
        cin >> v;
        TD::graph[i].push_back(v);
        TD::graph[v].push_back(i);
    }

    TD::DFS1(1);

    // 预处理每次 + 1 对答案的贡献 (depth + 1) ^ k - depth ^ k
    for (int i = 1; i <= n; i++)
        powers[i] = (power(TD::depth[i], k) - power(TD::depth[i] - 1, k) + MOD) % MOD;

    TD::DFS2(1, 1);
    TD::SGT.build();

    for (int i = 1, x, y; i <= q; i++) {
        cin >> x >> y;
        queries.emplace_back(x, y, i);
    }

    sort(queries.begin(), queries.end());

    int node = 0;
    for (auto [p, x, i] : queries) {
        while (node < p) TD::update_val_on_path(1, ++node);
        answers[i] = TD::query_sum_of_path(1, x);
    }

    for (int i = 1; i <= q; i++)
        cout << answers[i] << endl;

    return fflush(stdout), 0;
}
