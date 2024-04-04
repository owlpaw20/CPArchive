// 参考题解：https://ddosvoid.github.io/2022/05/08/Luogu-U216697-线段树区间历史版本和/

#include <iostream>

#define endl '\n'

using std::cin;
using std::cout;

using i64 = int64_t;

const int MAX_N = 1e5 + 5;

int N, M;
int a[MAX_N];

struct SEGTREE {
    struct NODE {
        int l, r;
        i64 sum, hsum;
        i64 add, hadd, time;

        NODE() {}
        NODE(i64 tag, i64 htag, i64 ti) : add(tag), hadd(htag), time(ti) {}

        void pull(const NODE x, const NODE y) {
            sum = x.sum + y.sum;
            hsum = x.hsum + y.hsum;
        }

        void modify(const NODE rt) {
            hsum += sum * rt.time + rt.hadd * (r - l + 1);
            sum += rt.add * (r - l + 1);
            hadd += rt.time * add + rt.hadd;
            add += rt.add;
            time += rt.time;
        }

        void push(NODE &x, NODE &y) {
            x.modify(NODE(add, hadd, time)), y.modify(NODE(add, hadd, time));
            add = hadd = time = 0;
        }

    } node[MAX_N << 2];

    void build(int l, int r, int u = 1) {
        node[u].l = l;
        node[u].r = r;

        if (l == r) {
            node[u].sum = node[u].hsum = a[l];
            node[u].add = node[u].time = 0;
            return;
        }

        int mid = (l + r) >> 1;

        build(l, mid, u << 1);
        build(mid + 1, r, u << 1 | 1);

        node[u].pull(node[u << 1], node[u << 1 | 1]);
    }

    void add(const int l, const int r, const i64 x, int u = 1) {
        if (node[u].l >= l && node[u].r <= r) return node[u].modify(NODE(x, 0, 0));

        if (node[u].time || node[u].add || node[u].hadd)
            node[u].push(node[u << 1], node[u << 1 | 1]);

        int mid = (node[u].l + node[u].r) >> 1;

        if (l <= mid) add(l, r, x, u << 1);
        if (r > mid) add(l, r, x, u << 1 | 1);

        node[u].pull(node[u << 1], node[u << 1 | 1]);
    }

    i64 query(const int l, const int r, int u = 1) {
        if (node[u].l >= l && node[u].r <= r) return node[u].hsum;

        if (node[u].time || node[u].add || node[u].hadd)
            node[u].push(node[u << 1], node[u << 1 | 1]);

        int mid = (node[u].l + node[u].r) >> 1;
        i64 ret = 0;

        if (l <= mid) ret += query(l, r, u << 1);
        if (r > mid) ret += query(l, r, u << 1 | 1);

        return ret;
    }
} SGT;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    for (int i = 1; i <= N; ++i) cin >> a[i];

    SGT.build(1, N);

    do {
        int type, l, r, x;
        cin >> type >> l >> r;

        if (type == 1)
            cin >> x, SGT.add(l, r, x);
        else
            cout << SGT.query(l, r) << endl;

        SGT.node[1].modify(SEGTREE::NODE(0, 0, 1));
    } while (--M);

    return fflush(stdout), 0;
}
