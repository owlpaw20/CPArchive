#pragma GCC optimize("O2,unroll-loops")

#include <array>
#include <cstdint>
#include <iostream>

#define endl '\n'

using std::array;
using std::cin;
using std::cout;

using i64 = int64_t;

const int MAX_N = 1e5 + 5;
const int MOD = 1e9 + 7;

int N, M;
int a[MAX_N];

namespace Matrix {
    using MATRIX = array<array<int, 2>, 2>;
    
    const MATRIX ZERO = {0, 0, 0, 0};
    const MATRIX UNIT = {1, 0, 0, 1};
    const MATRIX BASE = {1, 1, 1, 0};
    const MATRIX COEF = {1, 0, 1, 0};

    MATRIX operator*(const MATRIX X, const MATRIX Y) {
        MATRIX Z = ZERO;
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                for (int k = 0; k < 2; ++k)
                    Z[i][j] = ((i64)X[i][k] * Y[k][j] % MOD + Z[i][j]) % MOD;
        return Z;
    }

    MATRIX operator+(const MATRIX X, const MATRIX Y) {
        MATRIX Z = ZERO;
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j) Z[i][j] = (X[i][j] + Y[i][j]) % MOD;
        return Z;
    }

    MATRIX operator^(MATRIX X, i64 y) {
        MATRIX Z = UNIT;
        while (y) {
            if (y & 1) Z = Z * X;
            X = X * X;
            y >>= 1;
        }
        return Z;
    }
} // namespace Matrix
using namespace Matrix;

struct SEGTREE {
    struct NODE {
        MATRIX val, tag;

        void pull(const NODE x, const NODE y) {
            val = x.val + y.val;
        }
        void push(NODE &x, NODE &y) {
            x.val = x.val * tag;
            x.tag = x.tag * tag;
            y.val = y.val * tag;
            y.tag = y.tag * tag;
            tag = UNIT;
        }
    } node[MAX_N << 2];

    void build(int l, int r, int u = 1) {
        node[u].val = ZERO;
        node[u].tag = UNIT;

        if (l == r) {
            node[u].val = COEF * (BASE ^ (a[l] - 1));
            return;
        }

        int mid = (l + r) >> 1;

        build(l, mid, u << 1);
        build(mid + 1, r, u << 1 | 1);

        node[u].pull(node[u << 1], node[u << 1 | 1]);
    }

    void add(int l, int r, const MATRIX A, int u = 1, int nl = 1, int nr = N) {
        if (nl >= l && nr <= r) {
            node[u].val = node[u].val * A;
            node[u].tag = node[u].tag * A;
            return;
        }

        if (node[u].tag != UNIT) node[u].push(node[u << 1], node[u << 1 | 1]);

        int mid = (nl + nr) >> 1;

        if (l <= mid) add(l, r, A, u << 1, nl, mid);
        if (r > mid) add(l, r, A, u << 1 | 1, mid + 1, nr);

        node[u].pull(node[u << 1], node[u << 1 | 1]);
    }

    MATRIX query(int l, int r, int u = 1, int nl = 1, int nr = N) {
        if (nl >= l && nr <= r) return node[u].val;

        if (node[u].tag != UNIT) node[u].push(node[u << 1], node[u << 1 | 1]);

        int mid = (nl + nr) >> 1;

        MATRIX ret = ZERO;
        if (l <= mid) ret = ret + query(l, r, u << 1, nl, mid);
        if (r > mid) ret = ret + query(l, r, u << 1 | 1, mid + 1, nr);

        return ret;
    }
} SGT;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    for (int i = 1; i <= N; ++i) cin >> a[i];

    SGT.build(1, N);

    do {
        int type, l, r, x;
        cin >> type >> l >> r;

        if (type == 1)
            cin >> x, SGT.add(l, r, BASE ^ x);
        else
            cout << SGT.query(l, r)[1][0] % MOD << endl;
    } while (--M);

    return fflush(stdout), 0;
}
