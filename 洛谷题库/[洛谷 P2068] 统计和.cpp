#include <vector>
#include <iostream>
using namespace std;
using i64 = long long;

struct Fenwick {
    int size;
    vector<i64> tree;
    int lowbit(int x) {
        return x & -x;
    }
    void update(int x, i64 delta) {
        for (int i = x; i <= size; i += lowbit(i))
            tree[i] += delta;
    }
    i64 query(int x) {
        i64 ret = 0LL;
        for (int i = x; i; i -= lowbit(i))
            ret += tree[i];
        return ret;
    }
    void init(int n) {
        tree.clear();
        tree.resize(n + 5);
        size = n;
    }
};

int n, m;
Fenwick tr;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    tr.init(n);

    while (m--) {
        char opr;
        cin >> opr;
        if (opr == 'x') {
            int a, b;
            cin >> a >> b;
            tr.update(a, b);
        } else {
            int a, b;
            cin >> a >> b;
            cout << tr.query(b) - tr.query(a - 1) << endl;
        }
    }
    return 0;
}
