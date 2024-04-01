#include <iostream>

#define endl '\n'

using namespace std;
using Long = long long;

const int N = 5e5 + 10;

int n, m;
Long a[N];

Long GCD(Long x, Long y) {
    if (y == 0) return x;
    return GCD(y, x % y);
}

struct SegmentTree {
    struct Node {
        int l, r;
        Long sum, gcd;
    } tree[4 * N];

    void pushup(Node& u, Node& l, Node& r) {
        u.sum = l.sum + r.sum;
        u.gcd = GCD(l.gcd, r.gcd);
    }

    void build(int u, int l, int r) {
        if (l == r) {
            Long d = a[l] - a[l - 1];
            tree[u] = (Node) {
                l, r, d, d
            };
            return;
        }
        tree[u].l = l, tree[u].r = r;
        int mid = (l + r) >> 1;
        build(2 * u, l, mid);
        build(2 * u + 1, mid + 1, r);
        pushup(tree[u], tree[2 * u], tree[2 * u + 1]);
    }

    Node query(int u, int l, int r) {
        int tl = tree[u].l, tr = tree[u].r;
        if (tl >= l && tr <= r) return tree[u];
        int mid = (tl + tr) >> 1;
        if (r <= mid) return query(2 * u, l, r);
        if (l > mid) return query(2 * u + 1, l, r);
        Node left = query(2 * u, l, r);
        Node right = query(2 * u + 1, l, r);
        Node ret;
        pushup(ret, left, right);
        return ret;
    }

    void modify(int u, int tar, Long val) {
        int tl = tree[u].l, tr = tree[u].r;
        if (tl == tar && tr == tar) {
            Long sum = tree[u].sum + val;
            tree[u] = (Node) {
                tar, tar, sum, sum
            };
            return;
        }
        int mid = (tl + tr) >> 1;
        if (tar <= mid) modify(2 * u, tar, val);
        else modify(2 * u + 1, tar, val);
        pushup(tree[u], tree[2 * u], tree[2 * u + 1]);
    }
} tr;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    tr.build(1, 1, n);

    while (m--) {
        char opt;
        int l, r;
        Long d;
        cin >> opt >> l >> r;
        if (opt == 'C') {
            cin >> d;
            tr.modify(1, l, d);
            if (r + 1 <= n) tr.modify(1, r + 1, -d);
        } else if (opt == 'Q') {
            SegmentTree::Node left = tr.query(1, 1, l);
            SegmentTree::Node right = {0, 0, 0, 0};
            if (l + 1 <= r) right = tr.query(1, l + 1, r);
            cout << abs(GCD(left.sum, right.gcd)) << endl;
        }
    }

    fflush(stdout);
    return 0;
}
