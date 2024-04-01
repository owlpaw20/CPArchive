#pragma GCC optimize("Ofast")

#include <climits>
#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;

const int N = 1e6 + 10;

struct SegTree {
    struct Node {
        int l, r;
        int Max; // 区间最大值
        int sec; // 区间严格次大值
        int cnt; // 区间最大值的数量
        i64 sum, tag;
    };
    int a[N];
    Node tree[4 * N];

    void maintain(int u) {
        Node& root = tree[u];
        Node& left = tree[u << 1];
        Node& right = tree[u << 1 | 1];
        root.sum = left.sum + right.sum;
        if (left.Max == right.Max) {
            root.Max = left.Max;
            root.cnt = left.cnt + right.cnt;
            root.sec = max(left.sec, right.sec);
        } else if (left.Max > right.Max) {
            root.Max = left.Max;
            root.cnt = left.cnt;
            root.sec = max(left.sec, right.Max);
        } else {
            root.Max = right.Max;
            root.cnt = right.cnt;
            root.sec = max(right.sec, left.Max);
        }
    }

    void tagging(int u, i64 tag) {
        if (tree[u].Max <= tag) return;
        tree[u].sum += (1LL * tag - tree[u].Max) * tree[u].cnt;
        tree[u].Max = tree[u].tag = tag;
    }

    void propagate(int u) {
        if (tree[u].tag == -1) return;
        tagging(u << 1, tree[u].tag);
        tagging(u << 1 | 1, tree[u].tag);
        tree[u].tag = -1;
    }

    void build(int l, int r, int u = 1) {
        tree[u].l = l;
        tree[u].r = r;
        tree[u].tag = -1;
        if (l == r) {
            tree[u].sum = tree[u].Max = a[l];
            tree[u].sec = -1;
            tree[u].cnt = 1;
            return;
        }
        int mid = (l + r) >> 1;
        build(l, mid, u << 1);
        build(mid + 1, r, u << 1 | 1);
        maintain(u);
    }

    void update_min(int l, int r, int tag, int u = 1) {
        if (tree[u].Max <= tag) return;
        int tl = tree[u].l, tr = tree[u].r;
        if (tl >= l && tr <= r && tree[u].sec < tag)
            return tagging(u, tag);
        propagate(u);
        int mid = (tl + tr) >> 1;
        if (l <= mid) update_min(l, r, tag, u << 1);
        if (r > mid) update_min(l, r, tag, u << 1 | 1);
        maintain(u);
    }

    int query_max(int l, int r, int u = 1) {
        int tl = tree[u].l, tr = tree[u].r;
        if (tl >= l && tr <= r)
            return tree[u].Max;
        propagate(u);
        int mid = (tl + tr) >> 1;
        int ret1 = -1, ret2 = -1;
        if (l <= mid) ret1 = query_max(l, r, u << 1);
        if (r > mid) ret2 = query_max(l, r, u << 1 | 1);
        return max(ret1, ret2);
    }

    i64 query_sum(int l, int r, int u = 1) {
        int tl = tree[u].l, tr = tree[u].r;
        if (tl >= l && tr <= r)
            return tree[u].sum;
        propagate(u);
        int mid = (tl + tr) >> 1;
        i64 ret = 0;
        if (l <= mid) ret += query_sum(l, r, u << 1);
        if (r > mid) ret += query_sum(l, r, u << 1 | 1);
        return ret;
    }
};

int n, m, T;
SegTree SGT;

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> SGT.a[i];

    SGT.build(1, n);

    int opt, x, y, t;
    while (m--) {
        cin >> opt;
        if (opt == 0) {
            cin >> x >> y >> t;
            SGT.update_min(x, y, t);
        } else if (opt == 1) {
            cin >> x >> y;
            cout << SGT.query_max(x, y) << '\n';
        } else {
            cin >> x >> y;
            cout << SGT.query_sum(x, y) << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) solve();

    fflush(stdout);
    return 0;
}
