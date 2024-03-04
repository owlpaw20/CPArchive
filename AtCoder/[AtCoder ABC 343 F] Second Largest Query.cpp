#include <iostream>

#define endl '\n'

using namespace std;

const int N = 2e5 + 5;

int n, q;

struct SegTree {
    struct Node {
        int l, r;
        int max1, maxcnt1;
        int max2, maxcnt2;
    } node[N << 2];

    Node pushup(Node lc, Node rc) {
        Node rt;

        rt.l = lc.l;
        rt.r = rc.r;

        if (lc.max1 > rc.max1) {
            rt.max1 = lc.max1;
            rt.maxcnt1 = lc.maxcnt1;
            if (lc.max2 > rc.max1) {
                rt.max2 = lc.max2;
                rt.maxcnt2 = lc.maxcnt2;
            } else if (lc.max2 == rc.max1) {
                rt.max2 = lc.max2;
                rt.maxcnt2 = lc.maxcnt2 + rc.maxcnt1;
            } else {
                rt.max2 = rc.max1;
                rt.maxcnt2 = rc.maxcnt1;
            }
        } else if (rc.max1 > lc.max1) {
            rt.max1 = rc.max1;
            rt.maxcnt1 = rc.maxcnt1;
            if (rc.max2 > lc.max1) {
                rt.max2 = rc.max2;
                rt.maxcnt2 = rc.maxcnt2;
            } else if (lc.max1 == rc.max2) {
                rt.max2 = rc.max2;
                rt.maxcnt2 = lc.maxcnt1 + rc.maxcnt2;
            } else {
                rt.max2 = lc.max1;
                rt.maxcnt2 = lc.maxcnt1;
            }
        } else {
            rt.max1 = lc.max1;
            rt.maxcnt1 = lc.maxcnt1 + rc.maxcnt1;
            if (lc.max2 > rc.max2) {
                rt.max2 = lc.max2;
                rt.maxcnt2 = lc.maxcnt2;
            } else if (lc.max2 == rc.max2) {
                rt.max2 = lc.max2;
                rt.maxcnt2 = lc.maxcnt2 + rc.maxcnt2;
            } else {
                rt.max2 = rc.max2;
                rt.maxcnt2 = rc.maxcnt2;
            }
        }

        return rt;
    }

    void build(int l, int r, int u = 1) {
        node[u].l = l;
        node[u].r = r;

        if (l == r) {
            int x;
            cin >> x;
            node[u].max1 = x;
            node[u].max2 = -1;
            node[u].maxcnt1 = 1;
            node[u].maxcnt2 = 0;
            return;
        }

        int mid = (l + r) >> 1;

        build(l, mid, u << 1);
        build(mid + 1, r, u << 1 | 1);

        node[u] = pushup(node[u << 1], node[u << 1 | 1]);
    }

    void update(int x, int v, int u = 1) {
        if (node[u].l == node[u].r)
            return (void)(node[u].max1 = v);

        int mid = (node[u].l + node[u].r) >> 1;

        if (x <= mid) update(x, v, u << 1);
        else update(x, v, u << 1 | 1);

        node[u] = pushup(node[u << 1], node[u << 1 | 1]);
    }

    Node query(int l, int r, int u = 1) {
        if (node[u].l >= l && node[u].r <= r)
            return node[u];

        int mid = (node[u].l + node[u].r) >> 1;
        bool flag1 = false, flag2 = false;

        if (l <= mid) flag1 = true;
        if (r > mid) flag2 = true;

        if (flag1 && !flag2) return query(l, r, u << 1);
        if (flag2 && !flag1) return query(l, r, u << 1 | 1);
        return pushup(query(l, r, u << 1), query(l, r, u << 1 | 1));
    }
} SGT;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    SGT.build(1, n);

    while (q--) {
        int type, x, y;
        cin >> type >> x >> y;

        if (type == 1) SGT.update(x, y);
        else cout << SGT.query(x, y).maxcnt2 << endl;
    }

    return fflush(stdout), 0;
}
