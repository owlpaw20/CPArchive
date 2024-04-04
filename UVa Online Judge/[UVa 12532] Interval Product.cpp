#include <vector>
#include <iostream>

#define endl '\n'

using namespace std;
using cint = const int;

struct SegTree {
    struct Node {
        int l, r;
        int prod;
    };

    vector<int> x;
    vector<Node> tr;

    int &operator[](cint idx) {
        return x[idx];
    }

    void init(cint n) {
        x.clear();
        tr.clear();
        x.resize(n + 5);
        tr.resize(n * 4 + 20);
    }

    void maintain(cint u) {
        tr[u].prod = tr[u << 1].prod * tr[u << 1 | 1].prod;
    }

    void build(cint l, cint r, cint u = 1) {
        tr[u] = {l, r, 1};
        if (l == r)
            return (void)(tr[u].prod = x[l]);
        int mid = (l + r) >> 1;
        build(l, mid, u << 1);
        build(mid + 1, r, u << 1 | 1);
        maintain(u);
    }

    void update(cint i, cint v, cint u = 1) {
        if (tr[u].l == tr[u].r)
            return (void)(tr[u].prod = v);
        int mid = (tr[u].l + tr[u].r) >> 1;
        if (i <= mid) update(i, v, u << 1);
        else update(i, v, u << 1 | 1);
        maintain(u);
    }

    int query(cint l, cint r, cint u = 1) {
        if (tr[u].l >= l && tr[u].r <= r)
            return tr[u].prod;
        int mid = (tr[u].l + tr[u].r) >> 1;
        int ret = 1;
        if (l <= mid) ret *= query(l, r, u << 1);
        if (r > mid) ret *= query(l, r, u << 1 | 1);
        return ret;
    }
};

int n, K;
SegTree SGT;

int minimize(int x, int type) {
    if (x > 0) return (type == 1 ? 1 : (int)'+');
    if (x < 0) return (type == 1 ? -1 : (int)'-');
    return (type == 1 ? 0 : (int)'0');
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n >> K) {
        SGT.init(n);
        for (int i = 1, t; i <= n; i++)
            cin >> t, SGT[i] = minimize(t, 1);

        SGT.build(1, n);

        while (K--) {
            char type;
            int x, y;

            cin >> type >> x >> y;
            if (type == 'C')
                SGT.update(x, minimize(y, 1));
            else
                cout.put(minimize(SGT.query(x, y), 2));
        }

        cout.put(endl);
    }

    fflush(stdout);
    return 0;
}
