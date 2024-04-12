#include <iostream>

#define endl '\n'

using namespace std;

const int N = 5e5 + 5;

int n, q;
bool a[N];

struct SegTree {
    struct {
        int l, r;
        int sum;
        bool tag;
    } node[N << 2];

    void maintain(int u) {
        node[u].sum = node[u << 1].sum + node[u << 1 | 1].sum;
    }

    void propagate(int u) {
        auto &root = node[u];
        auto &left = node[u << 1];
        auto &right = node[u << 1 | 1];

        if (root.tag) {
            left.tag ^= 1;
            right.tag ^= 1;
            left.sum = left.r - left.l + 1 - left.sum;
            right.sum = right.r - right.l + 1 - right.sum;
            root.tag = 0;
        }
    }

    void build(int u, int l, int r) {
        node[u].l = l;
        node[u].r = r;
        node[u].tag = 0;

        if (l == r)
            return (void)(node[u].sum = a[l]);

        int mid = (l + r) >> 1;

        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);

        maintain(u);
    }

    void flip(int u, int l, int r) {
        int nl = node[u].l, nr = node[u].r;

        if (nl >= l && nr <= r) {
            node[u].tag ^= 1;
            node[u].sum = nr - nl + 1 - node[u].sum;
            return;
        }

        propagate(u);

        int mid = (nl + nr) >> 1;

        if (l <= mid) flip(u << 1, l, r);
        if (r > mid) flip(u << 1 | 1, l, r);

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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        char ch;
        cin >> ch;
        a[i] = (ch == '1') ^ (i % 2);
    }

    SGT.build(1, 1, n);

    while (q--) {
        int type, l, r;
        cin >> type >> l >> r;

        if (type == 1)
            SGT.flip(1, l, r);
        else {
            int ret = SGT.query(1, l, r);
            if (ret == 0 || ret == r - l + 1)
                puts("Yes");
            else
                puts("No");
        }
    }

    return fflush(stdout), 0;
}
