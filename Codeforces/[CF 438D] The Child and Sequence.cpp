#include <vector>
#include <iostream>

using namespace std;
using i64 = long long;

struct SegTree {
    struct Node {
        int l, r;
        int rmax;  // 维护区间最大值，优化时间复杂度
        i64 rsum;
    };
    vector<int> array;
    vector<Node> tree;

    void init(int n, const vector<int> &arr) {
        array = arr;
        tree.clear();
        tree.resize(n * 4 + 50);
    }

    void maintain(int u) {
        tree[u].rsum = tree[u << 1].rsum + tree[u << 1 | 1].rsum;
        tree[u].rmax = max(tree[u << 1].rmax, tree[u << 1 | 1].rmax);
    }

    void build(int l, int r, int u = 1) {
        if (l == r)
            return (void)(tree[u] = {l, r, array[l], array[l]});
        tree[u] = {l, r, 0, 0};
        int mid = (l + r) >> 1;
        build(l, mid, u << 1);
        build(mid + 1, r, u << 1 | 1);
        maintain(u);
    }

    void overwrite(int i, int x, int u = 1) {
        int tl = tree[u].l, tr = tree[u].r;
        if (tl == tr) {
            tree[u].rsum = x;
            tree[u].rmax = x;
            return;
        }
        int mid = (tl + tr) >> 1;
        if (i <= mid)
            overwrite(i, x, u << 1);
        else
            overwrite(i, x, u << 1 | 1);
        maintain(u);
    }

    void modulo(int l, int r, int mod, int u = 1) {
        int tl = tree[u].l, tr = tree[u].r;
        if (tree[u].rmax < mod)   // 如果当前区间的最大值都不超过模数
            return;               // 整个区间就没有更新的必要了
        if (tl == tr) {           // 否则如果递归到了单点
            tree[u].rmax %= mod;  // 更新取模之后的区间最大值
            tree[u].rsum %= mod;  // 更新取模之后的区间和
            return;
        }
        int mid = (tl + tr) >> 1;
        if (l <= mid) modulo(l, r, mod, u << 1);
        if (r > mid) modulo(l, r, mod, u << 1 | 1);
        maintain(u);
    }

    i64 query(int l, int r, int u = 1) {
        int tl = tree[u].l, tr = tree[u].r;
        if (tl >= l && tr <= r)
            return tree[u].rsum;
        int mid = (tl + tr) >> 1;
        i64 ret = 0;
        if (l <= mid) ret += query(l, r, u << 1);
        if (r > mid) ret += query(l, r, u << 1 | 1);
        return ret;
    }
};

int n, m;
SegTree SGT;
vector<int> a;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    SGT.init(n, a);
    SGT.build(1, n);

    while (m--) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r;
            cin >> l >> r;
            cout << SGT.query(l, r) << endl;
        } else if (type == 2) {
            int l, r, x;
            cin >> l >> r >> x;
            SGT.modulo(l, r, x);
        } else {
            int k, x;
            cin >> k >> x;
            SGT.overwrite(k, x);
        }
    }

    return 0;
}
