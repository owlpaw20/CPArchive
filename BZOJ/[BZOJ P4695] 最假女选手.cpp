#include <climits>
#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;

namespace FastIO {
    i64 read() {
        i64 x = 0, f = 1;
        char ch = getchar();
        while (ch < '0' || ch > '9') {
            if (ch == '-')
                f = -f;
            ch = getchar();
        }
        while (ch >= '0' && ch <= '9')
            x = x * 10 + (ch ^ 48), ch = getchar();
        return x * f;
    }
    void write(i64 x) {
        if (x < 0) putchar('-'), x = -x;
        if (x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
} // namespace FastIO
using namespace FastIO;

const int N = 5e5 + 5;

struct SegTreeBeats {
    struct Node {
        int l, r;
        int max1, max2, maxt, maxcnt;
        int min1, min2, mint, mincnt;
        int addt;
        i64 sum;
    } node[N << 2];

    int n, a[N];

    void init(int l, int *x) {
        n = l;
        for (int i = 1; i <= l; i++)
            a[i] = x[i];
    }

    void maintain(int u) {
        Node &root = node[u];
        Node &left = node[u << 1];
        Node &right = node[u << 1 | 1];

        root.sum = left.sum + right.sum;

        if (left.max1 == right.max1) {
            root.max1 = left.max1;
            root.max2 = max(left.max2, right.max2);
            root.maxcnt = left.maxcnt + right.maxcnt;
        } else if (left.max1 > right.max1) {
            root.max1 = left.max1;
            root.max2 = max(left.max2, right.max1);
            root.maxcnt = left.maxcnt;
        } else {
            root.max1 = right.max1;
            root.max2 = max(left.max1, right.max2);
            root.maxcnt = right.maxcnt;
        }

        if (left.min1 == right.min1) {
            root.min1 = left.min1;
            root.min2 = min(left.min2, right.min2);
            root.mincnt = left.mincnt + right.mincnt;
        } else if (left.min1 > right.min1) {
            root.min1 = right.min1;
            root.min2 = min(left.min1, right.min2);
            root.mincnt = right.mincnt;
        } else {
            root.min1 = left.min1;
            root.min2 = min(left.min2, right.min1);
            root.mincnt = left.mincnt;
        }
    }

    void build(int u, int l, int r) {
        node[u].l = l, node[u].r = r;
        node[u].maxt = INT_MIN;
        node[u].mint = INT_MAX;

        if (l == r) {
            node[u].sum = node[u].max1 = node[u].min1 = a[l];
            node[u].max2 = INT_MIN, node[u].min2 = INT_MAX;
            node[u].maxcnt = node[u].mincnt = 1;
            return;
        }

        int mid = (l + r) >> 1;

        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);

        maintain(u);
    }

    void tag_add(int u, int l, int r, int x) {
        node[u].sum += (r - l + 1LL) * x;
        node[u].max1 += x;
        node[u].min1 += x;
        node[u].addt += x;

        if (node[u].max2 != INT_MIN) node[u].max2 += x;
        if (node[u].min2 != INT_MAX) node[u].min2 += x;
        if (node[u].maxt != INT_MIN) node[u].maxt += x;
        if (node[u].mint != INT_MAX) node[u].mint += x;
    }

    void tag_min(int u, int x) {
        if (node[u].max1 <= x) return;

        node[u].sum += (x * 1LL - node[u].max1) * node[u].maxcnt;

        if (node[u].min2 == node[u].max1) node[u].min2 = x;
        if (node[u].min1 == node[u].max1) node[u].min1 = x;
        if (node[u].maxt > x) node[u].maxt = x;

        node[u].max1 = node[u].mint = x;
    }

    void tag_max(int u, int x) {
        if (node[u].min1 > x) return;

        node[u].sum += (x * 1LL - node[u].min1) * node[u].mincnt;

        if (node[u].max2 == node[u].min1) node[u].max2 = x;
        if (node[u].max1 == node[u].min1) node[u].max1 = x;
        if (node[u].mint < x) node[u].mint = x;

        node[u].min1 = node[u].maxt = x;
    }

    void propagate(int u) {
        if (node[u].addt) {
            int mid = (node[u].l + node[u].r) >> 1;
            tag_add(u << 1, node[u].l, mid, node[u].addt);
            tag_add(u << 1 | 1, mid + 1, node[u].r, node[u].addt);
            node[u].addt = 0;
        }

        if (node[u].maxt != INT_MIN) {
            tag_max(u << 1, node[u].maxt);
            tag_max(u << 1 | 1, node[u].maxt);
            node[u].maxt = INT_MIN;
        }

        if (node[u].mint != INT_MAX) {
            tag_min(u << 1, node[u].mint);
            tag_min(u << 1 | 1, node[u].mint);
            node[u].mint = INT_MAX;
        }
    }

    void range_add(int u, int l, int r, int delta) {
        int nl = node[u].l, nr = node[u].r;
        if (nl >= l && nr <= r)
            return tag_add(u, nl, nr, delta);

        propagate(u);

        int mid = (nl + nr) >> 1;

        if (l <= mid) range_add(u << 1, l, r, delta);
        if (r > mid) range_add(u << 1 | 1, l, r, delta);

        maintain(u);
    }

    void range_flatten_min(int u, int l, int r, int x) {
        if (node[u].max1 <= x) return;
        int nl = node[u].l, nr = node[u].r;
        if (nl >= l && nr <= r && node[u].max2 < x)
            return tag_min(u, x);

        propagate(u);

        int mid = (nl + nr) >> 1;

        if (l <= mid) range_flatten_min(u << 1, l, r, x);
        if (r > mid) range_flatten_min(u << 1 | 1, l, r, x);

        maintain(u);
    }

    void range_flatten_max(int u, int l, int r, int x) {
        if (node[u].min1 >= x) return;
        int nl = node[u].l, nr = node[u].r;
        if (nl >= l && nr <= r && node[u].min2 > x)
            return tag_max(u, x);

        propagate(u);

        int mid = (nl + nr) >> 1;

        if (l <= mid) range_flatten_max(u << 1, l, r, x);
        if (r > mid) range_flatten_max(u << 1 | 1, l, r, x);

        maintain(u);
    }

    i64 query_sum(int u, int l, int r) {
        int nl = node[u].l, nr = node[u].r;
        if (nl >= l && nr <= r)
            return node[u].sum;

        propagate(u);

        int mid = (nl + nr) >> 1;
        i64 sum = 0;

        if (l <= mid) sum += query_sum(u << 1, l, r);
        if (r > mid) sum += query_sum(u << 1 | 1, l, r);

        return sum;
    }

    int query_min(int u, int l, int r) {
        int nl = node[u].l, nr = node[u].r;
        if (nl >= l && nr <= r)
            return node[u].min1;

        propagate(u);

        int mid = (nl + nr) >> 1, mn = INT_MAX;

        if (l <= mid) mn = min(mn, query_min(u << 1, l, r));
        if (r > mid) mn = min(mn, query_min(u << 1 | 1, l, r));

        return mn;
    }

    int query_max(int u, int l, int r) {
        int nl = node[u].l, nr = node[u].r;
        if (nl >= l && nr <= r)
            return node[u].max1;

        propagate(u);

        int mid = (nl + nr) >> 1, mx = INT_MIN;

        if (l <= mid) mx = max(mx, query_max(u << 1, l, r));
        if (r > mid) mx = max(mx, query_max(u << 1 | 1, l, r));

        return mx;
    }
};

int n, m;
int a[N];
SegTreeBeats STB;

int main() {
    n = read();
    for (int i = 1; i <= n; i++) a[i] = read();

    STB.init(n, a);
    STB.build(1, 1, n);

    m = read();
    while (m--) {
        int t, l, r;
        t = read(), l = read(), r = read();
        if (t == 1) STB.range_add(1, l, r, read());
        else if (t == 2) STB.range_flatten_max(1, l, r, read());
        else if (t == 3) STB.range_flatten_min(1, l, r, read());
        else if (t == 4) write(STB.query_sum(1, l, r)), putchar('\n');
        else if (t == 5) write(STB.query_max(1, l, r)), putchar('\n');
        else if (t == 6) write(STB.query_min(1, l, r)), putchar('\n');
    }

    return fflush(stdout), 0;
}
