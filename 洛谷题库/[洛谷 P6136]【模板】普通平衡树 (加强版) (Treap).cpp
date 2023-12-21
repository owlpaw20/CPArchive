#include <random>
#include <climits>
#include <iostream>

#define endl '\n'

using namespace std;

namespace FastIO {
    int read() {
        int x = 0, f = 1;
        char ch = getchar();
        while (ch < '0' || ch > '9') {
            if (ch == '-')
                f = -f;
            ch = getchar();
        }
        while (ch >= '0' && ch <= '9')
            x = x * 10 + ch - 48, ch = getchar();
        return x * f;
    }
    void write(int x) {
        if (x < 0) putchar('-'), x = -x;
        if (x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
}  // namespace FastIO
using namespace FastIO;

const int SIZE = 2e6 + 10;  // 平衡树的空间复杂度是线性的

struct Treap {
    struct Node {
        int l, r;       // 左右子节点在数组中的下标
        int key, pri;   // 当前节点的权值和优先级
        int cnt, size;  // 当前节点的数的出现次数和当前节点为根节点的子树里数的总个数
    } tr[SIZE];

    int idx, root;

    // 在 Treap 上新建一个节点
    int create_node(int key) {
        tr[idx].key = key;
        tr[idx].pri = rand();
        tr[idx].cnt = 1;
        tr[idx].size = 1;
        return idx++;
    }

    // 更新以当前节点为根的子树里数的总个数
    void maintain(int u) {
        tr[u].size = tr[tr[u].l].size + tr[tr[u].r].size + tr[u].cnt;
    }

    // 初始化 Treap
    void init() {
        root = create_node(INT_MIN);
        tr[root].r = create_node(INT_MAX);
        maintain(root);
    }

    // 查询某数值的排名
    int get_rank_of_key(int u, int key) {
        if (u == 0) return 0;
        if (key == tr[u].key) return tr[tr[u].l].size + 1;
        if (key < tr[u].key) return get_rank_of_key(tr[u].l, key);
        return get_rank_of_key(tr[u].r, key) + tr[tr[u].l].size + tr[u].cnt;
    }

    // 查询某排名的数值
    int get_key_at_rank(int u, int rnk) {
        if (u == 0) return INT_MAX;
        if (rnk <= tr[tr[u].l].size) return get_key_at_rank(tr[u].l, rnk);
        if (rnk - tr[tr[u].l].size <= tr[u].cnt) return tr[u].key;
        return get_key_at_rank(tr[u].r, rnk - tr[tr[u].l].size - tr[u].cnt);
    }

    // 右旋：右旋拎左右挂左
    void rotate_right(int& fa) {
        int ls = tr[fa].l;
        tr[fa].l = tr[ls].r;
        tr[ls].r = fa;
        fa = ls;
        maintain(tr[ls].r);
        maintain(fa);
    }

    // 左旋：左旋拎右左挂右
    void rotate_left(int& fa) {
        int rs = tr[fa].r;
        tr[fa].r = tr[rs].l;
        tr[rs].l = fa;
        fa = rs;
        maintain(tr[rs].l);
        maintain(fa);
    }

    // 向 Treap 中插入数值
    void insert(int& u, int key) {
        if (u == 0)
            return (void)(u = create_node(key));

        if (key == tr[u].key) {
            tr[u].cnt++;
            maintain(u);
        } else if (key < tr[u].key) {
            insert(tr[u].l, key);
            if (tr[u].pri < tr[tr[u].l].pri) rotate_right(u);
            maintain(u);
        } else {
            insert(tr[u].r, key);
            if (tr[u].pri < tr[tr[u].r].pri) rotate_left(u);
            maintain(u);
        }
    }

    // 查询给定数值的前驱
    int get_predecessor(int key) {
        int idx = 1, u = root;

        while (u) {
            if (key == tr[u].key) {
                if (tr[u].l > 0) {
                    u = tr[u].l;
                    while (tr[u].r > 0)
                        u = tr[u].r;
                    idx = u;
                }
                break;
            }

            if (tr[u].key < key && tr[u].key > tr[idx].key) idx = u;
            u = (key < tr[u].key) ? tr[u].l : tr[u].r;
        }

        return tr[idx].key;
    }

    // 查询给定数值的后继
    int get_successor(int key) {
        int idx = 2, u = root;

        while (u) {
            if (key == tr[u].key) {
                if (tr[u].r > 0) {
                    u = tr[u].r;
                    while (tr[u].l > 0)
                        u = tr[u].l;
                    idx = u;
                }
                break;
            }

            if (tr[u].key > key && tr[u].key < tr[idx].key) idx = u;
            u = (key < tr[u].key) ? tr[u].l : tr[u].r;
        }

        return tr[idx].key;
    }

    // 在 Treap 中删除数值
    void remove(int& u, int key) {
        if (u == 0) return;

        if (key == tr[u].key) {
            if (tr[u].cnt > 1) {
                tr[u].cnt--;
                maintain(u);
                return;
            }

            if (tr[u].l || tr[u].r) {
                if (tr[u].r == 0 || tr[tr[u].l].pri > tr[tr[u].r].pri)
                    rotate_right(u), remove(tr[u].r, key);
                else
                    rotate_left(u), remove(tr[u].l, key);
                return maintain(u);
            }

            u = 0;
        }

        remove(key < tr[u].key ? tr[u].l : tr[u].r, key);
        maintain(u);
    }

    Treap() : idx(1), root(-1) {}
};

int n, m;
Treap treap;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    treap.init();

    n = read(), m = read();

    while (n--)
        treap.insert(treap.root, read());

    int lst = 0;
    int ans = 0;

    while (m--) {
        int opt, x;
        opt = read(), x = read();
        x ^= lst;
        if (opt == 1) treap.insert(treap.root, x);
        else if (opt == 2) treap.remove(treap.root, x);
        else if (opt == 3)
            treap.insert(treap.root, x),
                lst = treap.get_rank_of_key(treap.root, x) - 1,
                ans ^= lst,
                treap.remove(treap.root, x);
        else if (opt == 4) lst = treap.get_key_at_rank(treap.root, x + 1), ans ^= lst;
        else if (opt == 5) lst = treap.get_predecessor(x), ans ^= lst;
        else if (opt == 6) lst = treap.get_successor(x), ans ^= lst;
    }

    write(ans), putchar('\n');
    fflush(stdout);
    return 0;
}
