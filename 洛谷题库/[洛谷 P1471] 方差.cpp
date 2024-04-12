#include <iostream>

#define endl '\n'

using namespace std;
using f64 = double;

const int N = 1e5 + 5;

int n;
f64 a[N];

struct SegTree {
    struct {
        int l, r;
        f64 sum, sqr, tag;
    } node[N << 2];

    void pushup(int u) {
        node[u].sum = node[u << 1].sum + node[u << 1 | 1].sum;
        node[u].sqr = node[u << 1].sqr + node[u << 1 | 1].sqr;
    }

    void pushdown(int u) {
        auto &rt = node[u];
        auto &lc = node[u << 1];
        auto &rc = node[u << 1 | 1];

        if (rt.tag != 0) {
            lc.tag += rt.tag;
            rc.tag += rt.tag;
            lc.sqr += lc.sum * rt.tag * 2 + (lc.r - lc.l + 1) * rt.tag * rt.tag;
            rc.sqr += rc.sum * rt.tag * 2 + (rc.r - rc.l + 1) * rt.tag * rt.tag;
            lc.sum += (lc.r - lc.l + 1) * rt.tag;
            rc.sum += (rc.r - rc.l + 1) * rt.tag;
            rt.tag = 0;
        }
    }

    void build(int l = 1, int r = n, int u = 1) {
        node[u].l = l;
        node[u].r = r;
        node[u].tag = 0;

        if (l == r) {
            node[u].sum = a[l];
            node[u].sqr = a[l] * a[l];
            return;
        }

        int mid = (l + r) >> 1;

        build(l, mid, u << 1);
        build(mid + 1, r, u << 1 | 1);

        pushup(u);
    }

    void range_add(int l, int r, f64 x, int u = 1) {
        if (node[u].l >= l && node[u].r <= r) {
            node[u].tag += x;
            node[u].sqr += node[u].sum * x * 2 + (node[u].r - node[u].l + 1) * x * x;
            node[u].sum += (node[u].r - node[u].l + 1) * x;
            return;
        }

        pushdown(u);

        int mid = (node[u].l + node[u].r) >> 1;

        if (l <= mid) range_add(l, r, x, u << 1);
        if (r > mid) range_add(l, r, x, u << 1 | 1);

        pushup(u);
    }

    f64 query_range_sum(int l, int r, int u = 1) {
        if (node[u].l >= l && node[u].r <= r)
            return node[u].sum;

        pushdown(u);

        int mid = (node[u].l + node[u].r) >> 1;
        f64 ret = 0;

        if (l <= mid) ret += query_range_sum(l, r, u << 1);
        if (r > mid) ret += query_range_sum(l, r, u << 1 | 1);

        return ret;
    }

    f64 query_range_square_sum(int l, int r, int u = 1) {
        if (node[u].l >= l && node[u].r <= r)
            return node[u].sqr;

        pushdown(u);

        int mid = (node[u].l + node[u].r) >> 1;
        f64 ret = 0;

        if (l <= mid) ret += query_range_square_sum(l, r, u << 1);
        if (r > mid) ret += query_range_square_sum(l, r, u << 1 | 1);

        return ret;
    }
} SGT;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(4);

    int m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];

    SGT.build();

    while (m--) {
        int type, x, y;
        f64 k;

        cin >> type >> x >> y;

        if (type == 1) {
            cin >> k;
            SGT.range_add(x, y, k);
        } else if (type == 2) {
            f64 sum = SGT.query_range_sum(x, y);
            cout << fixed << sum / (y - x + 1) << endl;
        } else {
            f64 sum = SGT.query_range_sum(x, y);
            f64 sqr = SGT.query_range_square_sum(x, y);
            f64 avg = sum / (y - x + 1);
            cout << fixed << sqr / (y - x + 1) - avg * avg << endl;
        }
    }

    return fflush(stdout), 0;
}
