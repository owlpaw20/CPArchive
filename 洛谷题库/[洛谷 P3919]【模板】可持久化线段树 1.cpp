#include <vector>
#include <iostream>
#define endl '\n'

using namespace std;

struct PrstSegTree {
    struct Node {
        int l, r;
        int val;
    };

    vector<int> x;
    vector<Node> tree;

    // 可持久化数组动态加点
    int clone(int u) {
        tree.push_back(tree[u]);
        return tree.size() - 1;
    }

    // 可持久化数组建树
    int build(int u, int l, int r) {
        tree.emplace_back();
        u = tree.size() - 1;
        if (l == r) {
            tree[u].val = x[l];
            return u;
        }
        int mid = (l + r) >> 1;
        tree[u].l = build(tree[u].l, l, mid);
        tree[u].r = build(tree[u].r, mid + 1, r);
        return u;
    }

    // 可持久化数组单点更新
    int update(int u, int l, int r, int x, int val) {
        u = clone(u);
        if (l == r) {
            tree[u].val = val;
            return u;
        }
        int mid = (l + r) >> 1;
        if (x <= mid) tree[u].l = update(tree[u].l, l, mid, x, val);
        else tree[u].r = update(tree[u].r, mid + 1, r, x, val);
        return u;
    }

    // 可持久化数组单点查询
    int query(int u, int l, int r, int x) {
        if (l == r)
            return tree[u].val;
        int mid = (l + r) >> 1;
        if (x <= mid) return query(tree[u].l, l, mid, x);
        return query(tree[u].r, mid + 1, r, x);
    }
};

int n, m;
PrstSegTree PST;
vector<int> root;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    PST.x.resize(n);
    for (int i = 0; i < n; i++) cin >> PST.x[i];
    root.push_back(PST.build(0, 0, n - 1));

    while (m--) {
        int version, type;
        cin >> version >> type;
        if (type == 1) {
            int x, val;
            cin >> x >> val;
            root.push_back(PST.update(root[version], 0, n - 1, x - 1, val));
        } else {
            int x;
            cin >> x;
            cout << PST.query(root[version], 0, n - 1, x - 1) << endl;
            root.push_back(root[version]);
        }
    }

    fflush(stdout);
    return 0;
}
