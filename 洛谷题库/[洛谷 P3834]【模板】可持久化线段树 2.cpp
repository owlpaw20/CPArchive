#include <vector>
#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;

struct PrstSegTree {
    struct Node {
        int l, r;
        int cnt;
    };

    // 最大可能达到的空间是初始一棵树的 4 * N 加上更改过程新增的 N log N 个节点
    vector<Node> tree;

    // 可持久化线段树建树操作
    int build(int l, int r) {
        tree.emplace_back();
        int u = tree.size() - 1;
        if (l == r) return u;
        int mid = (l + r) >> 1;
        tree[u].l = build(l, mid);
        tree[u].r = build(mid + 1, r);
        return u;
    }

    // 可持久化线段树插入元素操作
    int insert(int u, int l, int r, int x) {
        tree.push_back(tree[u]);
        int v = tree.size() - 1; // 复制一个节点

        if (l == r) { // 如果找到了叶子节点
            tree[v].cnt++; // 当前位置的元素个数 + 1
            return v;
        }

        int mid = (l + r) >> 1;
        if (x <= mid) tree[v].l = insert(tree[u].l, l, mid, x);
        else tree[v].r = insert(tree[u].r, mid + 1, r, x);

        tree[v].cnt = tree[tree[v].l].cnt + tree[tree[v].r].cnt;
        return v;
    }

    // 可持久化线段树查找 [L, R] 中第 K 小元素的下标
    int query(int u, int v, int l, int r, int k) {
        if (l == r) return l; // 如果找到了目标位置就直接返回
        int cnt = tree[tree[u].l].cnt - tree[tree[v].l].cnt;

        int mid = (l + r) >> 1;

        if (k <= cnt) return query(tree[u].l, tree[v].l, l, mid, k);
        return query(tree[u].r, tree[v].r, mid + 1, r, k - cnt); // 剔除掉左子树中比目标元素要大的
    }
};

int n, m;
PrstSegTree PST;
vector<int> num, tmp;
vector<int> root;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    num.resize(n);
    for (int i = 0; i < n; i++)
        cin >> num[i];

    tmp = num;
    sort(num.begin(), num.end());
    num.erase(unique(num.begin(), num.end()), num.end());

    root.push_back(PST.build(0, n - 1));

    for (int i = 0; i < n; i++) {
        int pos = lower_bound(num.begin(), num.end(), tmp[i]) - num.begin();
        root.push_back(PST.insert(root[i], 0, n - 1, pos));
    }

    while (m--) {
        int l, r, k;
        cin >> l >> r >> k;
        cout << num[PST.query(root[r], root[l - 1], 0, n - 1, k)] << endl;
    }

    fflush(stdout);
    return 0;
}
