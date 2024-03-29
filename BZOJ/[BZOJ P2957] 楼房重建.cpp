#include <iostream>

#define endl '\n'

using std::cin;
using std::cout;

using f64 = double;

const int MAX_N = 1e5 + 5;

int N, M;

struct SEGTREE {
    struct NODE {
        f64 max;
        int len;
    } node[MAX_N << 2];

    int calc(const f64 k, int u = 1, int nl = 1, int nr = N) {
        if (nl == nr) return node[u].max > k;
        int mid = (nl + nr) >> 1;
        if (node[u << 1].max <= k) return calc(k, u << 1 | 1, mid + 1, nr);
        return node[u].len - node[u << 1].len + calc(k, u << 1, nl, mid);
    }

    void update(const int x, const f64 k, int u = 1, int nl = 1, int nr = N) {
        if (nl == nr) {
            node[u].max = k;
            node[u].len = 1;
            return;
        }

        int mid = (nl + nr) >> 1;

        if (x <= mid)
            update(x, k, u << 1, nl, mid);
        else
            update(x, k, u << 1 | 1, mid + 1, nr);

        node[u].max = std::max(node[u << 1].max, node[u << 1 | 1].max);
        node[u].len = node[u << 1].len + calc(node[u << 1].max, u << 1 | 1, mid + 1, nr);
    }
} SGT;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;

    while (M--) {
        int x, y;
        cin >> x >> y;
        SGT.update(x, (f64)y / x);
        cout << SGT.node[1].len << endl;
    }

    return fflush(stdout), 0;
}
