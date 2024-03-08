#include <iostream>
using namespace std;
using i64 = long long;

const int N = 1e5 + 10;

int n, m;
int a[N];

struct SegTree {
    struct Node {
        int l, r;
        i64 total, add;
    } tree[4 * N];
    void maintain(int u) {
        tree[u].total = tree[2 * u].total + tree[2 * u + 1].total;
    }
    void propagate(int u) {
        Node& root = tree[u];
        Node& left = tree[2 * u];
        Node& right = tree[2 * u + 1];
        if (root.add) {
            left.add += root.add;
            right.add += root.add;
            left.total += root.add * (left.r - left.l + 1);
            right.total += root.add * (right.r - right.l + 1);
            root.add = 0;
        }
    }
    void build(int u, int l, int r) {
        if (l == r)
            return (void)(tree[u] = {l, r, a[l], 0});
        tree[u] = {l, r};
        int mid = (l + r) >> 1;
        build(2 * u, l, mid);
        build(2 * u + 1, mid + 1, r);
        maintain(u);
    }
    void update(int u, int l, int r, i64 delta) {
        int tl = tree[u].l, tr = tree[u].r;
        if (tl >= l && tr <= r) {
            tree[u].add += delta;
            tree[u].total += delta * (tr - tl + 1);
            return;
        }
        propagate(u);
        int mid = (tl + tr) >> 1;
        if (l <= mid) update(2 * u, l, r, delta);
        if (r > mid) update(2 * u + 1, l, r, delta);
        maintain(u);
    }
    i64 query(int u, int l, int r) {
        int tl = tree[u].l, tr = tree[u].r;
        if (tl >= l && tr <= r)
            return tree[u].total;
        propagate(u);
        int mid = (tl + tr) >> 1;
        i64 ret = 0;
        if (l <= mid) ret += query(2 * u, l, r);
        if (r > mid) ret += query(2 * u + 1, l, r);
        return ret;
    }
} tr;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    tr.build(1, 1, n);

    while (m--) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int x, y, k;
            cin >> x >> y >> k;
            tr.update(1, x, y, k);
        } else {
            int x, y;
            cin >> x >> y;
            cout << tr.query(1, x, y) << endl;
        }
    }
    return 0;
}
