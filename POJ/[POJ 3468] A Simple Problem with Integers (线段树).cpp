#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;

const int N = 1e5 + 5;

struct SegTree {
    struct Node {
        int l, r;
        i64 sum, add;
    } node[N << 2];

    int a[N];

    void init(int x, int* v) {
        for (int i = 1; i <= x; i++)
            a[i] = v[i];
    }

    void maintain(int u) {
        node[u].sum = node[u << 1].sum + node[u << 1 | 1].sum;
    }

    void propagate(int u) {
        Node& root = node[u];
        Node& left = node[u << 1];
        Node& right = node[u << 1 | 1];

        if (root.add) {
            left.add += root.add;
            left.sum += (left.r - left.l + 1LL) * root.add;
            right.add += root.add;
            right.sum += (right.r - right.l + 1LL) * root.add;
            root.add = 0;
        }
    }

    void build(int u, int l, int r) {
        node[u].l = l;
        node[u].r = r;

        if (l == r) {
            node[u].add = 0;
            node[u].sum = a[l];
            return;
        }

        int mid = (l + r) >> 1;

        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);

        maintain(u);
    }

    void update(int u, int l, int r, int x) {
        int nl = node[u].l, nr = node[u].r;

        if (nl >= l && nr <= r) {
            node[u].add += x;
            node[u].sum += (nr - nl + 1LL) * x;
            return;
        }

        propagate(u);

        int mid = (nl + nr) >> 1;

        if (l <= mid) update(u << 1, l, r, x);
        if (r > mid) update(u << 1 | 1, l, r, x);

        maintain(u);
    }

    i64 query(int u, int l, int r) {
        int nl = node[u].l, nr = node[u].r;

        if (nl >= l && nr <= r)
            return node[u].sum;

        propagate(u);

        int mid = (nl + nr) >> 1;
        i64 ret = 0;

        if (l <= mid) ret += query(u << 1, l, r);
        if (r > mid) ret += query(u << 1 | 1, l, r);

        return ret;
    }
};

int n, q;
int a[N];
SegTree SGT;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];

    SGT.init(n, a);
    SGT.build(1, 1, n);

    while (q--) {
        char type;
        int l, r, x;

        cin >> type >> l >> r;

        if (type == 'C') {
            cin >> x;
            SGT.update(1, l, r, x);
        } else
            cout << SGT.query(1, l, r) << endl;
    }

    return fflush(stdout), 0;
}
