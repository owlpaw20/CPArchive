#include <vector>
#include <climits>
#include <iostream>
using namespace std;
using i64 = long long;

struct SegTree {
    struct Node {
        int l, r;
        i64 Min, sum, add;
    };
    vector<int> array;
    vector<Node> tree;
    void init(int n) {
        tree.clear();
        array.clear();
        array.resize(n + 10);
        tree.resize(n * 4 + 40);
    }
    void maintain(int u) {
        tree[u].Min = min(tree[u << 1].Min, tree[u << 1 | 1].Min);
        tree[u].sum = tree[u << 1].sum + tree[u << 1 | 1].sum;
    }
    void propagate(int u) {
        Node &root = tree[u];
        Node &left = tree[u << 1];
        Node &right = tree[u << 1 | 1];
        if (root.add) {
            left.add += root.add;
            left.Min += root.add;
            left.sum += (left.r - left.l + 1) * root.add;
            right.add += root.add;
            right.Min += root.add;
            right.sum += (right.r - right.l + 1) * root.add;
            root.add = 0;
        }
    }
    void build(int l, int r, int u = 1) {
        if (l == r)
            return (void)(tree[u] = {l, r, array[l], array[l], 0LL});
        tree[u] = {l, r, INT_MAX, 0LL, 0LL};
        int mid = (l + r) >> 1;
        build(l, mid, u << 1);
        build(mid + 1, r, u << 1 | 1);
        maintain(u);
    }
    void update(int l, int r, i64 delta, int u = 1) {
        int tl = tree[u].l, tr = tree[u].r;
        if (tl >= l && tr <= r) {
            tree[u].add += delta;
            tree[u].Min += delta;
            tree[u].sum += delta * (tr - tl + 1);
            return;
        }
        propagate(u);
        int mid = (tl + tr) >> 1;
        if (l <= mid) update(l, r, delta, u << 1);
        if (r > mid) update(l, r, delta, u << 1 | 1);
        maintain(u);
    }
    i64 get_min(int l, int r, int u = 1) {
        int tl = tree[u].l, tr = tree[u].r;
        if (tl >= l && tr <= r)
            return tree[u].Min;
        propagate(u);
        i64 ret = INT_MAX;
        int mid = (tl + tr) >> 1;
        if (l <= mid) ret = min(ret, get_min(l, r, u << 1));
        if (r > mid) ret = min(ret, get_min(l, r, u << 1 | 1));
        return ret;
    }
    i64 count(int l, int r, int u = 1) {
        int tl = tree[u].l, tr = tree[u].r;
        if (tl >= l && tr <= r)
            return tree[u].sum;
        propagate(u);
        i64 ret = 0;
        int mid = (tl + tr) >> 1;
        if (l <= mid) ret += count(l, r, u << 1);
        if (r > mid) ret += count(l, r, u << 1 | 1);
        return ret;
    }
} SGT;

int n, q;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    SGT.init(n);
    for (int i = 1; i <= n; i++)
        cin >> SGT.array[i];
    SGT.build(1, n);

    while (q--) {
        char opt;
        cin >> opt;
        if (opt == 'M') {
            int l, r;
            cin >> l >> r;
            cout << SGT.get_min(l, r) << endl;
        } else if (opt == 'S') {
            int l, r;
            cin >> l >> r;
            cout << SGT.count(l, r) << endl;
        } else {
            int l, r, x;
            cin >> l >> r >> x;
            SGT.update(l, r, x);
        }
    }
    return 0;
}
