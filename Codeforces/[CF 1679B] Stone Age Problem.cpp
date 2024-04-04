#include <vector>
#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;

namespace FastIO {
    using Long = long long;
    Long read() {
        Long x = 0, f = 1;
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
    void write(Long x) {
        if (x < 0) putchar('-'), x = -x;
        if (x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
} // namespace FastIO
using namespace FastIO;

struct SegTree {
    struct Node {
        int l, r, tag;
        i64 sum;
    };

    vector<int> a;
    vector<Node> t;

    void init(int n) {
        n += 5;
        a.clear();
        t.clear();
        a.resize(n);
        t.resize(n << 2);
    }

    void maintain(int u) {
        t[u].sum = t[u << 1].sum + t[u << 1 | 1].sum;
    }

    void propagate(int u) {
        Node &root = t[u];
        Node &left = t[u << 1];
        Node &right = t[u << 1 | 1];
        if (root.tag) {
            left.tag = root.tag;
            right.tag = root.tag;
            left.sum = (i64)(left.r - left.l + 1) * root.tag;
            right.sum = (i64)(right.r - right.l + 1) * root.tag;
            root.tag = 0;
        }
    }

    void build(int l, int r, int u = 1) {
        t[u].l = l;
        t[u].r = r;
        t[u].tag = 0LL;
        if (l == r)
            return (void)(t[u].sum = a[l]);
        int mid = (l + r) >> 1;
        build(l, mid, u << 1);
        build(mid + 1, r, u << 1 | 1);
        maintain(u);
    }

    void flatten(int l, int r, int x, int u = 1) {
        int tl = t[u].l, tr = t[u].r;
        if (tl >= l && tr <= r) {
            t[u].tag = x;
            t[u].sum = (i64)(tr - tl + 1) * x;
            return;
        }
        propagate(u);
        int mid = (tl + tr) >> 1;
        if (l <= mid) flatten(l, r, x, u << 1);
        if (r > mid) flatten(l, r, x, u << 1 | 1);
        maintain(u);
    }

    i64 query_sum(int l, int r, int u = 1) {
        int tl = t[u].l, tr = t[u].r;
        if (tl >= l && tr <= r)
            return t[u].sum;
        propagate(u);
        int mid = (tl + tr) >> 1;
        i64 ret = 0LL;
        if (l <= mid) ret += query_sum(l, r, u << 1);
        if (r > mid) ret += query_sum(l, r, u << 1 | 1);
        return ret;
    }
};

int n, q;
SegTree SGT;

int main() {
    n = read(), q = read();
    SGT.init(n);
    for (int i = 1; i <= n; i++)
        SGT.a[i] = read();

    SGT.build(1, n);

    int type, i, x;
    while (q--) {
        type = read();
        if (type == 1) {
            i = read(), x = read();
            SGT.flatten(i, i, x);
            write(SGT.query_sum(1, n)), putchar('\n');
        } else {
            x = read();
            SGT.flatten(1, n, x);
            write(SGT.query_sum(1, n)), putchar('\n');
        }
    }

    fflush(stdout);
    return 0;
}
