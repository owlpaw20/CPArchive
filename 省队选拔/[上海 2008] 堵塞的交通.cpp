#include <string>
#include <iostream>

#define endl '\n'

using std::cin;
using std::cout;
using std::string;

const int MAX_N = 1e5 + 5;

int M;
bool flag[MAX_N][2];

struct SEGTREE {
    struct NODE {
        int l, r;
        bool upper, lower, left, right, pdgnl, sdgnl;

        NODE() {}
        NODE(int _l, int _r, bool a, bool b, bool c, bool d, bool e, bool f) :
            l(_l), r(_r), upper(a), lower(b), left(c), right(d), pdgnl(e), sdgnl(f) {}

        NODE pull(const NODE &L, const NODE &R) {
            return NODE(l = L.l, r = R.r,
                    upper = (L.upper && flag[L.r][0] && R.upper) ||
                        (L.pdgnl && flag[L.r][1] && R.sdgnl),
                    lower = (L.lower && flag[L.r][1] && R.lower) ||
                        (L.sdgnl && flag[L.r][0] && R.pdgnl),
                    left = L.left ||
                        (L.upper && L.lower && R.left && flag[L.r][0] && flag[L.r][1]),
                    right = R.right ||
                        (R.upper && R.lower && L.right && flag[L.r][0] && flag[L.r][1]),
                    pdgnl = (L.pdgnl && flag[L.r][1] && R.lower) ||
                        (L.upper && flag[L.r][0] && R.pdgnl),
                    sdgnl = (L.sdgnl && flag[L.r][0] && R.upper) ||
                        (L.lower && flag[L.r][1] && R.sdgnl));
        }
    } node[MAX_N << 2];

    void build(int l, int r, int u = 1) {
        if (l == r) {
            node[u] = NODE(l, r, 1, 1, 0, 0, 0, 0);
            return;
        }

        int mid = (l + r) >> 1;

        build(l, mid, u << 1);
        build(mid + 1, r, u << 1 | 1);

        node[u].pull(node[u << 1], node[u << 1 | 1]);
    }

    void change_horizontal(int x, int y, bool status, int u = 1) {
        int mid = (node[u].l + node[u].r) >> 1;

        if (mid == x) {
            flag[x][y] = status;
            node[u].pull(node[u << 1], node[u << 1 | 1]);
            return;
        }

        if (x <= mid)
            change_horizontal(x, y, status, u << 1);
        else
            change_horizontal(x, y, status, u << 1 | 1);

        node[u].pull(node[u << 1], node[u << 1 | 1]);
    }

    void change_vertical(int x, bool status, int u = 1) {
        if (node[u].l == node[u].r) {
            node[u].left = status;
            node[u].right = status;
            node[u].pdgnl = status;
            node[u].sdgnl = status;
            return;
        }

        int mid = (node[u].l + node[u].r) >> 1;

        if (x <= mid)
            change_vertical(x, status, u << 1);
        else
            change_vertical(x, status, u << 1 | 1);

        node[u].pull(node[u << 1], node[u << 1 | 1]);
    }

    NODE query(int l, int r, int u = 1) {
        if (node[u].l >= l && node[u].r <= r) return node[u];

        int mid = (node[u].l + node[u].r) >> 1;

        if (r <= mid) return query(l, r, u << 1);
        if (l > mid) return query(l, r, u << 1 | 1);
        return NODE().pull(query(l, r, u << 1), query(l, r, u << 1 | 1));
    }
} SGT;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> M;

    SGT.build(1, M);

    while (true) {
        string s;
        int r1, c1, r2, c2;

        cin >> s;

        if (s == "Exit") break;

        cin >> r1 >> c1 >> r2 >> c2;

        if (s == "Close" || s == "Open") {
            if (r1 == r2)
                SGT.change_horizontal(std::min(c1, c2), r1 - 1, s == "Open");
            else
                SGT.change_vertical(c1, s == "Open");
        } else {
            if (c1 > c2) std::swap(r1, r2), std::swap(c1, c2);

            SEGTREE::NODE pre = SGT.query(1, c1);
            SEGTREE::NODE mid = SGT.query(c1, c2);
            SEGTREE::NODE suf = SGT.query(c2, M);

            bool flag = false;

            if (r1 == 1 && r2 == 1)
                flag = mid.upper || (pre.right && mid.lower && suf.left) ||
                    (pre.right && mid.sdgnl) || (mid.pdgnl && suf.left);
            else if (r1 == 1 && r2 == 2)
                flag = mid.pdgnl || (pre.right && mid.lower) || (mid.upper && suf.left) ||
                    (pre.right && mid.sdgnl && suf.left);
            else if (r1 == 2 && r2 == 1)
                flag = mid.sdgnl || (mid.upper && pre.right) || (suf.left && mid.lower) ||
                    (pre.right && mid.pdgnl && suf.left);
            else
                flag = mid.lower || (pre.right && mid.upper && suf.left) ||
                    (pre.right && mid.pdgnl) || (mid.sdgnl && suf.left);

            cout.put(flag ? 'Y' : 'N').put('\n');
        }
    }

    return fflush(stdout), 0;
}
