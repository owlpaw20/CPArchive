#include <iostream>
using namespace std;
using i64 = long long;

const int N = 1e5 + 10;

int n, p, q;
int a[N];

struct SegTree {
    struct Node {
        int l, r;
        i64 total, add, mul;
    } tree[4 * N];
    void maintain(int u) {
        tree[u].total = (tree[2 * u].total + tree[2 * u + 1].total) % p;
    }
    void propagate(int u) {
        Node& root = tree[u];
        Node& left = tree[2 * u];
        Node& right = tree[2 * u + 1];
        if (root.mul != 1) {
            left.add = left.add * root.mul % p;
            left.mul = left.mul * root.mul % p;
            left.total = left.total * root.mul % p;
            right.add = right.add * root.mul % p;
            right.mul = right.mul * root.mul % p;
            right.total = right.total * root.mul % p;
            root.mul = 1;
        }
        if (root.add != 0) {
            left.add = (left.add + root.add) % p;
            left.total = (left.total + (left.r - left.l + 1) * root.add % p) % p;
            right.add = (right.add + root.add) % p;
            right.total = (right.total + (right.r - right.l + 1) * root.add % p) % p;
            root.add = 0;
        }
    }
    void build(int u, int l, int r) {
        if (l == r)
            return (void)(tree[u] = {l, r, a[l] % p, 0, 1});
        tree[u].l = l, tree[u].r = r, tree[u].mul = 1;
        int mid = (l + r) >> 1;
        build(2 * u, l, mid);
        build(2 * u + 1, mid + 1, r);
        maintain(u);
    }
    void multiply(int u, int l, int r, i64 mtpr) {
        int tl = tree[u].l, tr = tree[u].r;
        if (tl >= l && tr <= r) {
            tree[u].add = tree[u].add * mtpr % p;
            tree[u].mul = tree[u].mul * mtpr % p;
            tree[u].total = tree[u].total * mtpr % p;
            return;
        }
        propagate(u);
        int mid = (tl + tr) >> 1;
        if (l <= mid) multiply(2 * u, l, r, mtpr);
        if (r > mid) multiply(2 * u + 1, l, r, mtpr);
        maintain(u);
    }
    void accumulate(int u, int l, int r, i64 delta) {
        int tl = tree[u].l, tr = tree[u].r;
        if (tl >= l && tr <= r) {
            tree[u].add = (tree[u].add + delta) % p;
            tree[u].total = (tree[u].total + delta * (tr - tl + 1) % p) % p;
            return;
        }
        propagate(u);
        int mid = (tl + tr) >> 1;
        if (l <= mid) accumulate(2 * u, l, r, delta);
        if (r > mid) accumulate(2 * u + 1, l, r, delta);
        maintain(u);
    }
    i64 query(int u, int l, int r) {
        int tl = tree[u].l, tr = tree[u].r;
        if (tl >= l && tr <= r)
            return tree[u].total;
        propagate(u);
        i64 ret = 0;
        int mid = (tl + tr) >> 1;
        if (l <= mid) ret = (ret + query(2 * u, l, r)) % p;
        if (r > mid) ret = (ret + query(2 * u + 1, l, r)) % p;
        return ret % p;
    }
} tr;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q >> p;
    for (int i = 1; i <= n; i++) cin >> a[i];
    tr.build(1, 1, n);

    while (q--) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int t, g, c;
            cin >> t >> g >> c;
            tr.multiply(1, t, g, c);
        } else if (opt == 2) {
            int t, g, c;
            cin >> t >> g >> c;
            tr.accumulate(1, t, g, c);
        } else {
            int t, g;
            cin >> t >> g;
            cout << tr.query(1, t, g) << endl;
        }
    }
    return 0;
}
