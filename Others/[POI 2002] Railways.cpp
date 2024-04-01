#include <iostream>
using namespace std;

namespace FastIO {
    int read() {
        int x = 0, f = 1;
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
    void read3(int& x, int& y, int& z) {
        x = read();
        y = read();
        z = read();
    }
} // namespace FastIO
using namespace FastIO;

const int N = 6e4 + 10;

int c, s, r;

struct SegmentTree {
    struct Node {
        int l, r;
        int sum, tag;
    } tree[4 * N];
    void pushup(int u) {
        tree[u].sum = max(tree[2 * u].sum, tree[2 * u + 1].sum);
    }
    void pushdown(int u) {
        Node& root = tree[u];
        Node& left = tree[2 * u];
        Node& right = tree[2 * u + 1];
        if (root.tag) {
            left.sum += root.tag;
            right.sum += root.tag;
            left.tag += root.tag;
            right.tag += root.tag;
            root.tag = 0;
        }
    }
    void build(int u, int l, int r) {
        if (l == r) tree[u] = {l, r, 0, 0};
        else {
            tree[u].l = l, tree[u].r = r;
            int mid = (l + r) >> 1;
            build(2 * u, l, mid);
            build(2 * u + 1, mid + 1, r);
        }
    }
    void modify(int u, int l, int r, int delta) {
        int tl = tree[u].l, tr = tree[u].r;
        if (tl >= l && tr <= r) {
            tree[u].tag += delta;
            tree[u].sum += delta;
            return;
        }
        pushdown(u);
        int mid = (tl + tr) >> 1;
        if (l <= mid) modify(2 * u, l, r, delta);
        if (r > mid) modify(2 * u + 1, l, r, delta);
        pushup(u);
    }
} tr;

int main() {
    read3(c, s, r);
    tr.build(1, 1, c);
    while (r--) {
        int o, d, n;
        read3(o, d, n);
        tr.modify(1, o, d - 1, n);
        if (tr.tree[1].sum > s) {
            puts("N");
            tr.modify(1, o, d - 1, -n);
        } else
            puts("T");
    }
    return 0;
}
