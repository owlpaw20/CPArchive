#include <numeric>
#include <iostream>

#define endl '\n'

using std::cin;
using std::cout;
using std::ios;

using u32 = unsigned int;
using u64 = unsigned long long;
using u128 = __uint128_t;

const int N = 2e5 + 5;
const u64 LMT = 1e18;

int n, m;
u64 a[N];

u64 lcm(u64 x, u64 y) {
    if (x > LMT || y > LMT) return LMT + 1;
    u64 LCM = (u128)x * y / std::gcd(x, y);
    if (LCM > LMT) return LMT + 1;
    return LCM;
}

#define nl node[u].l
#define nr node[u].r

struct SegTree {
    struct Node {
        int l, r;
        u32 sum;
        u64 lcm;
    } node[N << 2];

    void pushup(int u) {
        node[u].sum = node[u << 1].sum + node[u << 1 | 1].sum;
        node[u].lcm = lcm(node[u << 1].lcm, node[u << 1 | 1].lcm);
    }

    void build(int l = 1, int r = n, int u = 1) {
        nl = l, nr = r;

        if (l == r)
            return (void)(node[u].sum = node[u].lcm = a[l]);

        int mid = (l + r) >> 1;

        build(l, mid, u << 1);
        build(mid + 1, r, u << 1 | 1);

        pushup(u);
    }

    void update(int l, int r, u64 x, int u = 1) {
        if (node[u].lcm <= LMT && x % node[u].lcm == 0) return;

        if (nl == nr) {
            node[u].lcm = std::gcd(node[u].lcm, x);
            node[u].sum = node[u].lcm;
            return;
        }

        int mid = (nl + nr) >> 1;

        if (l <= mid) update(l, r, x, u << 1);
        if (r > mid) update(l, r, x, u << 1 | 1);

        pushup(u);
    }

    u32 sum(int l, int r, int u = 1) {
        if (nl >= l && nr <= r)
            return node[u].sum;

        int mid = (nl + nr) >> 1;
        u32 ret = 0;

        if (l <= mid) ret += sum(l, r, u << 1);
        if (r > mid) ret += sum(l, r, u << 1 | 1);

        return ret;
    }
} SGT;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];

    SGT.build();

    while (m--) {
        int type, l, r;
        u64 x;

        cin >> type >> l >> r;

        if (type == 1) cin >> x, SGT.update(l, r, x);
        else cout << SGT.sum(l, r) << endl;
    }

    return fflush(stdout), 0;
}
