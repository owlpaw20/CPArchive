#include <iostream>

#define endl '\n'

using namespace std;

const int SIZE = 1e5 + 10;

struct FHQTreap {
    struct Node {
        int l, r;
        int key, pri;
        int size; // 相同键值的节点是分开存储在不同节点上的，所以不需要 cnt 参数
    } tr[SIZE];

    int idx, root;

    // 新建节点
    int create_node(int key) {
        tr[idx].key = key;
        tr[idx].pri = rand();
        tr[idx].size = 1;
        tr[idx].l = tr[idx].r = 0;
        return idx++;
    }

    // 维护子树中数的总个数
    void maintain(int u) {
        tr[u].size = tr[tr[u].l].size + tr[tr[u].r].size + 1;
    }

    // FHQ Treap 分裂
    // `L` 与 `R` 分别代表分裂后的左右两个 Treap 的根节点
    void split(int u, int key, int &L, int &R) {
        if (u == 0) // 新建节点时初始化左右子树为 0 号节点
            return (void)(L = R = 0); // 表示没有左右子树，即到达了递归的终点

        if (tr[u].key <= key) // 如果当前节点小于或等于分界线的键值
            L = u, split(tr[u].r, key, tr[u].r, R); // 则将当前节点划入左子树，并在右子树继续分裂
        else if (tr[u].key > key) // 如果当前节点大于分界线的键值
            R = u, split(tr[u].l, key, L, tr[u].l); // 则将当前节点划入右子树，并在左子树继续分裂

        maintain(u);
    }

    // FHQ Treap 合并
    int join(int L, int R) {
        if (L == 0 || R == 0) // 如果左右 Treap 中有一个已经到达了叶子结点
            return L + R; // 则将剩下非叶子结点的子树作为合并之后的根节点

        if (tr[L].pri > tr[R].pri) { // 如果左 Treap 的优先级高于右 Treap
            tr[L].r = join(tr[L].r, R); // 则左 Treap 的右子树与右 Treap 合并
            maintain(L); // 维护合并后 Treap 的 size
            return L; // 返回合并后的根节点
        } else { // 如果右 Treap 的优先级高于左 Treap
            tr[R].l = join(L, tr[R].l); // 则右 Treap 的左子树与左 Treap 合并
            maintain(R); // 维护合并后 Treap 的 size
            return R; // 返回合并后的根节点
        }
    }

    // 插入键值
    void insert(int key) {
        int L, R;
        split(root, key, L, R); // 以需要插入的键值作为分界线将 Treap 分裂
        int pos = create_node(key); // 新建该键值的节点
        root = join(join(L, pos), R); // 插入节点并合并 Treap
    }

    // 删除节点
    void remove(int key) {
        int L, R, u;
        split(root, key, L, R); // 以需要删除的键值作为分界线将 Treap 分裂
        split(L, key - 1, L, u); // 将分裂出的左 Treap 进一步根据小于 key 和 等于 key 进行分裂
        u = join(tr[u].l, tr[u].r); // 直接合并 key 所在节点的左右 Treap，相当于忽略并删除了 key
        root = join(join(L, u), R); // 复原 Treap
    }

    // 查询某数值的排名
    int get_rank(int key) {
        int L, R;
        split(root, key - 1, L, R); // 以小于 key 的第一个数值作为分界线将 Treap 分裂
        int rnk = tr[L].size + 1; // 那么该子树的大小 + 1 便是 key 的最小排名
        join(L, R); // 复原 Treap
        return rnk; // 返回排名
    }

    // 查询某排名的节点
    int get_node(int u, int rnk) {
        if (rnk == tr[tr[u].l].size + 1) return u; // 排名恰好为当前节点
        if (rnk <= tr[tr[u].l].size) return get_node(tr[u].l, rnk); // 排名在左子树中
        return get_node(tr[u].r, rnk - tr[tr[u].l].size - 1); // 排名在右子树中
    }

    // 查询某排名的数值
    int get_key(int rt, int rnk) {
        return tr[get_node(rt, rnk)].key;
    }

    // 查询给定数值的前驱
    int get_predecessor(int key) {
        int L, R;
        split(root, key - 1, L, R); // 以小于 key 的第一个数值作为分界线将 Treap 分裂
        int ret = get_key(L, tr[L].size); // 查询左子树中最大的数，也就是 key 的前驱
        join(L, R); // 复原 Treap
        return ret; // 返回键值
    }

    // 查询给定数值的后继
    int get_successor(int key) {
        int L, R;
        split(root, key, L, R); // 以 key 作为分界线将 Treap 分裂
        int ret = get_key(R, 1); // 查询右子树中最小的数，也就是 key 的后继
        join(L, R); // 复原 Treap
        return ret; // 返回键值
    }

    FHQTreap() : idx(1), root(0) {}
};

int n;
FHQTreap treap;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    while (n--) {
        int opt, x;
        cin >> opt >> x;
        if (opt == 1) treap.insert(x);
        else if (opt == 2) treap.remove(x);
        else if (opt == 3) cout << treap.get_rank(x) << endl;
        else if (opt == 4) cout << treap.get_key(treap.root, x) << endl;
        else if (opt == 5) cout << treap.get_predecessor(x) << endl;
        else if (opt == 6) cout << treap.get_successor(x) << endl;
    }

    fflush(stdout);
    return 0;
}
