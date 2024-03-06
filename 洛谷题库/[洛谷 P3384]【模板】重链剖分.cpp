#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;
using lng = long long;

const int N = 1e5 + 5;
const int M = 2e5 + 5;

int n, m, root, mod;

struct SegTree {
    struct Node {
        int l, r;
        lng sum, add;
    } node[N << 2];

    int a[N];

    void init(int b[]) {
        for (int i = 1; i <= n; i++)
            a[i] = b[i];
    }

    void maintain(int u) { node[u].sum = (node[u << 1].sum + node[u << 1 | 1].sum) % mod; }

    void propagate(int u) {
        Node& root = node[u];
        Node& left = node[u << 1];
        Node& right = node[u << 1 | 1];

        if (root.add) {
            left.add = (left.add + root.add) % mod;
            right.add = (right.add + root.add) % mod;
            left.sum = (left.sum + (left.r - left.l + 1LL) * root.add) % mod;
            right.sum = (right.sum + (right.r - right.l + 1LL) * root.add) % mod;

            root.add = 0;
        }
    }

    void build(int u, int l, int r) {
        node[u].l = l;
        node[u].r = r;
        node[u].add = 0;

        if (l == r)
            return (void)(node[u].sum = a[l] % mod);

        int mid = (l + r) >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);

        maintain(u);
    }

    void inc(int u, int l, int r, int x) {
        int nl = node[u].l, nr = node[u].r;
        if (nl >= l && nr <= r) {
            node[u].add = (node[u].add + x) % mod;
            node[u].sum = (node[u].sum + (nr - nl + 1LL) * x) % mod;
            return;
        }

        propagate(u);

        int mid = (nl + nr) >> 1;
        if (l <= mid) inc(u << 1, l, r, x);
        if (r > mid) inc(u << 1 | 1, l, r, x);

        maintain(u);
    }

    int sum(int u, int l, int r) {
        int nl = node[u].l, nr = node[u].r;
        if (nl >= l && nr <= r)
            return node[u].sum % mod;

        propagate(u);

        int mid = (nl + nr) >> 1;
        lng ret = 0;
        if (l <= mid) ret += sum(u << 1, l, r);
        if (r > mid) ret += sum(u << 1 | 1, l, r);

        return ret % mod;
    }
} SGT;

namespace TreeDecomp {
    int ed[M], nx[M], head[N], val[N], idx;
    int fa[N], pref[N], depth[N], size[N], top[N];
    int dfn[N], newval[N], timestamp;

    void connect(int u, int v) {
        ed[idx] = v;
        nx[idx] = head[u];
        head[u] = idx++;
    }

    // 通过第一遍 DFS 来获取所有节点的深度、父节点、子树大小以及重子节点
    void DFS1(int u, int f) {
        fa[u] = f;                // 更新子节点的父节点
        size[u] = 1;              // 初始化当前节点韦为根的子树
        depth[u] = depth[f] + 1;  // 更新子节点深度

        for (int i = head[u]; ~i; i = nx[i]) {
            int v = ed[i];
            if (v == f) continue;

            DFS1(v, u);          // 向子节点递归
            size[u] += size[v];  // 将子树中节点的总数累加至当前节点上

            if (pref[u] == 0 ||           // 如果当前节点还没有重子节点
                size[pref[u]] < size[v])  // 或者此前确定的重子节点需要更新
                pref[u] = v;              // 则将其更新为当前子节点
        }
    }

    // 通过第二遍 DFS 来确定各个节点所属的重链及其子节点
    void DFS2(int u, int path_top) {
        top[u] = path_top;           // 通过递归传值记录各个节点所在重链的链头
        dfn[u] = ++timestamp;        // 更新节点的 DFS 序
        newval[timestamp] = val[u];  // 并标记该节点处的权值

        if (pref[u] == 0) return;  // 如果当前节点为叶子节点则退出

        DFS2(pref[u], path_top);  // 向重子节点递归
        for (int i = head[u]; ~i; i = nx[i])
            if (ed[i] != fa[u] && ed[i] != pref[u])
                DFS2(ed[i], ed[i]);  // 向所有轻子节点递归
    }

    // 更新路径上节点的权值
    void update_path_val(int u, int v, int x) {
        x %= mod;

        // 如果两个节点不在同一重链上
        while (top[u] != top[v]) {
            if (depth[top[u]] < depth[top[v]]) swap(u, v);  // 选择其中所在重链深度较大的节点
            SGT.inc(1, dfn[top[u]], dfn[u], x);             // 跳到该重链的顶端并维护向上跳的部分
            u = fa[top[u]];                                 // 跳到重链顶端节点的父节点
        }                                                   // 直到 u 和 v 到达同一重链上

        if (depth[u] > depth[v]) swap(u, v);
        SGT.inc(1, dfn[u], dfn[v], x);  // 维护同一重链上 u 和 v 之间的这一部分
    }

    // 查询路径上节点的权值和（同上）
    int query_path_sum(int u, int v) {
        int ret = 0;

        while (top[u] != top[v]) {
            if (depth[top[u]] < depth[top[v]]) swap(u, v);
            ret = (ret + SGT.sum(1, dfn[top[u]], dfn[u])) % mod;
            u = fa[top[u]];
        }

        if (depth[u] > depth[v]) swap(u, v);
        ret = (ret + SGT.sum(1, dfn[u], dfn[v])) % mod;

        return ret;
    }

    // 更新子树里节点的权值
    void update_subtree_val(int u, int x) {
        // 子树的 DFS 序范围起点 + 子树大小 - 1 = 子树的 DFS 序范围终点
        SGT.inc(1, dfn[u], dfn[u] + size[u] - 1, x);
    }

    // 查询子树的权值和（同上）
    int query_subtree_sum(int u) { return SGT.sum(1, dfn[u], dfn[u] + size[u] - 1); }
}  // namespace TreeDecomp
using namespace TreeDecomp;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(head, -1, sizeof head);

    cin >> n >> m >> root >> mod;

    for (int i = 1; i <= n; i++) cin >> val[i];
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        connect(u, v);
        connect(v, u);
    }

    DFS1(root, 0);
    DFS2(root, root);

    SGT.init(newval);
    SGT.build(1, 1, n);

    while (m--) {
        int type, l, r, x;
        cin >> type;

        if (type == 1) {
            cin >> l >> r >> x;
            update_path_val(l, r, x);
        } else if (type == 2) {
            cin >> l >> r;
            cout << query_path_sum(l, r) << endl;
        } else if (type == 3) {
            cin >> l >> x;
            update_subtree_val(l, x);
        } else {
            cin >> l;
            cout << query_subtree_sum(l) << endl;
        }
    }

    return fflush(stdout), 0;
}
