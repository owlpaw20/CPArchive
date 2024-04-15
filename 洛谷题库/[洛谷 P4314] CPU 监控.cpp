#include <limits>
#include <cstdint>
#include <iostream>

#define endl '\n'

using std::cin;
using std::cout;

using i64 = int64_t;

const int MAX_N = 1e5 + 5;
const i64 INF = std::numeric_limits<i64>::min();

int N, Q;
int a[MAX_N];

struct SEGTREE {
    struct NODE {
        i64 max, hmax;
        i64 add, hadd;
        i64 alt, halt;

        NODE() {}

        void pull(const NODE x, const NODE y) {
            max = std::max(x.max, y.max);
            hmax = std::max(x.hmax, y.hmax);
        }

        void modify_add(const i64 padd, const i64 phadd) {
            hmax = std::max(hmax, max + phadd);
            max += padd;
            if (alt == INF) {
                hadd = std::max(hadd, add + phadd);
                add += padd;
            } else {
                halt = std::max(halt, alt + phadd);
                alt += padd;
            }
        }

        void modify_alt(const i64 palt, const i64 phalt) {
            hmax = std::max(hmax, phalt);
            max = palt;
            halt = std::max(halt, phalt);
            alt = palt;
        }

        void push(NODE &x, NODE &y) {
            if (add || hadd) {
                x.modify_add(add, hadd);
                y.modify_add(add, hadd);
                add = hadd = 0;
            }

            if (alt != INF || halt != INF) {
                x.modify_alt(alt, halt);
                y.modify_alt(alt, halt);
                alt = halt = INF;
            }
        }

    } node[MAX_N << 2];

    void build(int l, int r, int u = 1) {
        node[u].alt = node[u].halt = INF;

        if (l == r) {
            node[u].max = node[u].hmax = a[l];
            return;
        }

        int mid = (l + r) >> 1;

        build(l, mid, u << 1);
        build(mid + 1, r, u << 1 | 1);

        node[u].pull(node[u << 1], node[u << 1 | 1]);
    }

    void update(const int l, const int r, const bool type, const i64 x, int u = 1,
        int nl = 1, int nr = N) {
        if (nl >= l && nr <= r) {
            type ? node[u].modify_alt(x, x) : node[u].modify_add(x, x);
            return;
        }

        if (node[u].add || node[u].hadd || node[u].alt != INF || node[u].halt != INF)
            node[u].push(node[u << 1], node[u << 1 | 1]);

        int mid = (nl + nr) >> 1;

        if (l <= mid) update(l, r, type, x, u << 1, nl, mid);
        if (r > mid) update(l, r, type, x, u << 1 | 1, mid + 1, nr);

        node[u].pull(node[u << 1], node[u << 1 | 1]);
    }

    NODE query(const int l, const int r, int u = 1, int nl = 1, int nr = N) {
        if (nl >= l && nr <= r) return node[u];

        if (node[u].add || node[u].hadd || node[u].alt != INF || node[u].halt != INF)
            node[u].push(node[u << 1], node[u << 1 | 1]);

        int mid = (nl + nr) >> 1;

        if (r <= mid) return query(l, r, u << 1, nl, mid);
        if (l > mid) return query(l, r, u << 1 | 1, mid + 1, nr);

        NODE ret;
        ret.pull(query(l, r, u << 1, nl, mid), query(l, r, u << 1 | 1, mid + 1, nr));
        return ret;
    }
} SGT;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for (int i = 1; i <= N; ++i) cin >> a[i];

    SGT.build(1, N);

    cin >> Q;
    do {
        char type;
        int l, r, x;

        cin >> type >> l >> r;

        if (type == 'Q')
            cout << SGT.query(l, r).max << endl;
        else if (type == 'A')
            cout << SGT.query(l, r).hmax << endl;
        else if (type == 'P')
            cin >> x, SGT.update(l, r, 0, x);
        else
            cin >> x, SGT.update(l, r, 1, x);

    } while (--Q);

    return fflush(stdout), 0;
}
