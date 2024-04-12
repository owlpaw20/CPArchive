#include <bitset>
#include <vector>
#include <iostream>

#define endl '\n'

using namespace std;
using BIT = bitset<35>;

struct SegTree {
    struct Node {
        int l, r;
        int alt;
        BIT colors;
        Node() {}
        Node(int _l, int _r) :
            l(_l), r(_r), alt(0) {
            colors[1] = 1;
        }
    };

    vector<Node> tree;
    int size;

    void init(int n) {
        size = n;
        tree.clear();
        tree.resize(n * 4 + 20);
    }

    void maintain(int u) {
        tree[u].colors = tree[u << 1].colors | tree[u << 1 | 1].colors;
    }
    void propagate(int u) {
        Node &root = tree[u];
        Node &left = tree[u << 1];
        Node &right = tree[u << 1 | 1];
        if (root.alt) {
            left.alt = root.alt;
            left.colors.reset();
            left.colors[root.alt] = 1;
            right.alt = root.alt;
            right.colors.reset();
            right.colors[root.alt] = 1;
            root.alt = 0;
        }
    }

    void build(int l, int r, int u = 1) {
        tree[u] = Node(l, r);
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(l, mid, u << 1);
        build(mid + 1, r, u << 1 | 1);
        maintain(u);
    }
    void update(int l, int r, int c, int u = 1) {
        int tl = tree[u].l, tr = tree[u].r;
        if (tl >= l && tr <= r) {
            tree[u].alt = c;
            tree[u].colors.reset();
            tree[u].colors[c] = 1;
            return;
        }
        propagate(u);
        int mid = (tl + tr) >> 1;
        if (l <= mid) update(l, r, c, u << 1);
        if (r > mid) update(l, r, c, u << 1 | 1);
        maintain(u);
    }
    BIT query(int l, int r, int u = 1) {
        int tl = tree[u].l, tr = tree[u].r;
        if (tl >= l && tr <= r)
            return tree[u].colors;
        propagate(u);
        BIT ret(0);
        int mid = (tl + tr) >> 1;
        if (l <= mid) ret |= query(l, r, u << 1);
        if (r > mid) ret |= query(l, r, u << 1 | 1);
        return ret;
    }
};

int n, m, q;
SegTree SGT;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> q;
    SGT.init(n);
    SGT.build(1, n);

    while (q--) {
        char opt;
        int l, r, c;
        cin >> opt >> l >> r;
        if (l > r) swap(l, r);
        if (opt == 'C') {
            cin >> c;
            SGT.update(l, r, c);
        } else
            cout << SGT.query(l, r).count() << endl;
    }

    fflush(stdout);
    return 0;
}
