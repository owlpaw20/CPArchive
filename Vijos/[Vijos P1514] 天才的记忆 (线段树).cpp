#include <vector>
#include <climits>
#include <iostream>

#define endl '\n'

using namespace std;

struct SegTree {
    struct Node {
        int l, r;
        int val, mx;
    };

    vector<int> x;
    vector<Node> t;

    void init(int n) {
        x.clear();
        t.clear();
        x.resize(n + 5);
        t.resize(n * 4 + 20);
    }

    void maintain(int u) {
        t[u].mx = max(t[u << 1].mx, t[u << 1 | 1].mx);
    }

    void build(int l, int r, int u = 1) {
        t[u].l = l;
        t[u].r = r;
        if (l == r)
            return (void)(t[u].val = t[u].mx = x[l]);
        int mid = (l + r) >> 1;
        build(l, mid, u << 1);
        build(mid + 1, r, u << 1 | 1);
        maintain(u);
    }

    int query(int l, int r, int u = 1) {
        if (t[u].l >= l && t[u].r <= r)
            return t[u].mx;
        int mid = (t[u].l + t[u].r) >> 1;
        int ret = INT_MIN;
        if (l <= mid) ret = max(ret, query(l, r, u << 1));
        if (r > mid) ret = max(ret, query(l, r, u << 1 | 1));
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
        cin >> SGT.x[i];
    SGT.build(1, n);

    cin >> m;
    while (m--) {
        int l, r;
        cin >> l >> r;
        cout << SGT.query(l, r) << endl;
    }

    fflush(stdout);
    return 0;
}
