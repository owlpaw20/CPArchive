#include <cmath>
#include <vector>
#include <iostream>

using namespace std;
using i64 = long long;
using PII = pair<int, int>;

struct SegTree {
    struct Node {
        int l, r;
        i64 sum, maxV;
    };

    vector<i64> a;
    vector<Node> tree;

    i64 &operator[](const int idx) {
        return a[idx];
    }

    void init(int n) {
        a.clear();
        a.resize(n + 5);
        tree.clear();
        tree.resize(n * 4 + 20);
    }

    void maintain(int u) {
        tree[u].sum = tree[u << 1].sum + tree[u << 1 | 1].sum;
        tree[u].maxV = max(tree[u << 1].maxV, tree[u << 1 | 1].maxV);
    }

    void build(int l, int r, int u = 1) {
        tree[u].l = l;
        tree[u].r = r;
        if (l == r) {
            tree[u].sum = a[l];
            tree[u].maxV = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(l, mid, u << 1);
        build(mid + 1, r, u << 1 | 1);
        maintain(u);
    }

    void rangeSqrt(int l, int r, int u = 1) {
        auto [tl, tr] = PII(tree[u].l, tree[u].r);
        if (tree[u].maxV <= 1) return;
        if (tl == tr) {
            tree[u].sum = sqrt(tree[u].sum);
            tree[u].maxV = sqrt(tree[u].maxV);
            return;
        }
        int mid = (tl + tr) >> 1;
        if (l <= mid) rangeSqrt(l, r, u << 1);
        if (r > mid) rangeSqrt(l, r, u << 1 | 1);
        maintain(u);
    }

    i64 queryRangeSum(int l, int r, int u = 1) {
        auto [tl, tr] = PII(tree[u].l, tree[u].r);
        if (tl >= l && tr <= r)
            return tree[u].sum;
        int mid = (tl + tr) >> 1;
        i64 ret = 0;
        if (l <= mid) ret += queryRangeSum(l, r, u << 1);
        if (r > mid) ret += queryRangeSum(l, r, u << 1 | 1);
        return ret;
    }
};

int n, m;
SegTree SGT;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    SGT.init(n);
    for (int i = 1; i <= n; i++)
        cin >> SGT[i];

    SGT.build(1, n);

    cin >> m;
    while (m--) {
        int K, l, r;
        cin >> K >> l >> r;
        if (l > r) swap(l, r);
        if (K == 0) SGT.rangeSqrt(l, r);
        if (K == 1) cout << SGT.queryRangeSum(l, r) << '\n';
    }

    fflush(stdout);
    return 0;
}
