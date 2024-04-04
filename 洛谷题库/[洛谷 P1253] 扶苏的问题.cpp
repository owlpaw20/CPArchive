#include <vector>
#include <climits>
#include <iostream>

#define endl '\n'
#define INF LONG_LONG_MIN

using namespace std;
using i64 = long long;

struct SegTree {
    struct Node {
        int l, r;
        i64 Max, alt, add;
    };

    vector<int> array;
    vector<Node> tree;

    void init(int n) {
        tree.clear();
        array.clear();
        array.resize(n + 10);
        tree.resize(n * 4 + 40);
    }

    void maintain(int u) {
        tree[u].Max = max(tree[u << 1].Max, tree[u << 1 | 1].Max);
    }

    void propagate(int u) {
        Node &root = tree[u];
        Node &left = tree[u << 1];
        Node &right = tree[u << 1 | 1];

        if (root.alt != INF) {
            left.add = 0LL;
            left.alt = root.alt;
            left.Max = root.alt;
            right.add = 0LL;
            right.alt = root.alt;
            right.Max = root.alt;
            root.alt = INF;
        }
        if (root.add) {
            left.add += root.add;
            left.Max += root.add;
            right.add += root.add;
            right.Max += root.add;
            root.add = 0;
        }
    }

    void build(int l, int r, int u = 1) {
        if (l == r)
            return (void)(tree[u] = {l, r, array[l], INF, 0LL});
        tree[u] = {l, r, 0, INF, 0LL};
        int mid = (l + r) >> 1;
        build(l, mid, u << 1);
        build(mid + 1, r, u << 1 | 1);
        maintain(u);
    }

    void alter(int l, int r, i64 val, int u = 1) {
        int tl = tree[u].l, tr = tree[u].r;
        if (tl >= l && tr <= r) {
            tree[u].add = 0LL;
            tree[u].alt = val;
            tree[u].Max = val;
            return;
        }
        propagate(u);
        int mid = (tl + tr) >> 1;
        if (l <= mid) alter(l, r, val, u << 1);
        if (r > mid) alter(l, r, val, u << 1 | 1);
        maintain(u);
    }

    void increase(int l, int r, i64 delta, int u = 1) {
        int tl = tree[u].l, tr = tree[u].r;
        if (tl >= l && tr <= r) {
            tree[u].add += delta;
            tree[u].Max += delta;
            return;
        }
        propagate(u);
        int mid = (tl + tr) >> 1;
        if (l <= mid) increase(l, r, delta, u << 1);
        if (r > mid) increase(l, r, delta, u << 1 | 1);
        maintain(u);
    }

    i64 query(int l, int r, int u = 1) {
        int tl = tree[u].l, tr = tree[u].r;
        if (tl >= l && tr <= r)
            return tree[u].Max;
        propagate(u);
        int mid = (tl + tr) >> 1;
        i64 ret = INF;
        if (l <= mid) ret = max(ret, query(l, r, u << 1));
        if (r > mid) ret = max(ret, query(l, r, u << 1 | 1));
        return ret;
    }
};

int n, q;
SegTree tr;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    tr.init(n);
    for (int i = 1; i <= n; i++)
        cin >> tr.array[i];

    tr.build(1, n);

    while (q--) {
        int opr;
        cin >> opr;
        if (opr == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            tr.alter(l, r, x);
        } else if (opr == 2) {
            int l, r, x;
            cin >> l >> r >> x;
            tr.increase(l, r, x);
        } else {
            int l, r;
            cin >> l >> r;
            cout << tr.query(l, r) << endl;
        }
    }

    fflush(stdout);
    return 0;
}
