#include <cmath>
#include <tuple>
#include <vector>
#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;
using T4I = tuple<i64, i64, i64, i64>;

const int INF = 0x3f3f3f3f;

struct SparseTables {
    using VI = vector<i64>;
    using VII = vector<VI>;

    VII all_mx, all_mn, neg_mx, pos_mn;

    void prep(int x, VI v) {
        for (int i = 1; i <= x; i++) {
            all_mx[i][0] = v[i];
            all_mn[i][0] = v[i];
            neg_mx[i][0] = (v[i] > 0 ? -INF : v[i]);
            pos_mn[i][0] = (v[i] < 0 ? INF : v[i]);
        }

        int lmt = ceil(log2(x)) + 1;
        for (int j = 1; j <= lmt; j++)
            for (int i = 1; i + (1 << j) - 1 <= x; i++) {
                all_mx[i][j] = max(all_mx[i][j - 1], all_mx[i + (1 << (j - 1))][j - 1]);
                all_mn[i][j] = min(all_mn[i][j - 1], all_mn[i + (1 << (j - 1))][j - 1]);
                neg_mx[i][j] = max(neg_mx[i][j - 1], neg_mx[i + (1 << (j - 1))][j - 1]);
                pos_mn[i][j] = min(pos_mn[i][j - 1], pos_mn[i + (1 << (j - 1))][j - 1]);
            }
    }

    T4I query(int l, int r) {
        int t = log2(r - l + 1);
        i64 ret1 = max(all_mx[l][t], all_mx[r - (1 << t) + 1][t]);
        i64 ret2 = min(all_mn[l][t], all_mn[r - (1 << t) + 1][t]);
        i64 ret3 = max(neg_mx[l][t], neg_mx[r - (1 << t) + 1][t]);
        i64 ret4 = min(pos_mn[l][t], pos_mn[r - (1 << t) + 1][t]);
        return make_tuple(ret1, ret2, ret3, ret4);
    }

    SparseTables(int x, VI v) {
        int lmt = ceil(log2(x)) + 1;
        all_mx.resize(x + 1, VI(lmt + 1, -INF));
        all_mn.resize(x + 1, VI(lmt + 1, INF));
        neg_mx.resize(x + 1, VI(lmt + 1, -INF));
        pos_mn.resize(x + 1, VI(lmt + 1, INF));
        prep(x, v);
    }
};

int n, m, q;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> q;

    vector<i64> a(n + 1), b(m + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++) cin >> b[i];

    SparseTables A(n, a), B(m, b);

    while (q--) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        T4I qa = A.query(l1, r1), qb = B.query(l2, r2);

        // tuple<0> = 区间最大值
        // tuple<1> = 区间最小值
        // tuple<2> = 区间非正最大值
        // tuple<3> = 区间非负最小值

        i64 ans = max(
                min(get<0>(qa) * get<1>(qb), get<0>(qa) * get<0>(qb)),
                min(get<1>(qa) * get<0>(qb), get<1>(qa) * get<1>(qb)));
        if (get<2>(qa) > -INF) ans = max(ans, get<2>(qa) * get<0>(qb));
        if (get<3>(qa) < INF) ans = max(ans, get<3>(qa) * get<1>(qb));
        cout << ans << endl;
    }

    fflush(stdout);
    return 0;
}
