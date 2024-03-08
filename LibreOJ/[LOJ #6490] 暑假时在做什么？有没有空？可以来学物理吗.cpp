#include <climits>
#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;

const int N = 1e5 + 5;
const int M = 20;

struct SparseTable {
    i64 mx[N][M];
    i64 mn[N][M];

    int log2(int x) {
        int exp = 0;
        while (x >>= 1)
            exp += 1;
        return exp;
    }

    void init(int x, i64* v) {
        for (int i = 0; i <= x; i++)
            mx[i][0] = mn[i][0] = v[i];
        for (int j = 1; 1 << j <= x; j++)
            for (int i = 0; i + (1 << j) - 1 <= x; i++) {
                mx[i][j] = max(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
                mn[i][j] = min(mn[i][j - 1], mn[i + (1 << (j - 1))][j - 1]);
            }
    }

    i64 query_max(int l, int r) {
        if (l > r) return INT_MIN;
        int t = log2(r - l + 1);
        return max(mx[l][t], mx[r - (1 << t) + 1][t]);
    }

    i64 query_min(int l, int r) {
        if (l > r) return INT_MAX;
        int t = log2(r - l + 1);
        return min(mn[l][t], mn[r - (1 << t) + 1][t]);
    }
};

int n, L, R;
int a[N];
i64 ans[N], p[N];
SparseTable ST;

void solve(int l, int r) {
    if (r - l + 1 < L) return;

    if (l == r) {
        if (L == 1)
            ans[l] = max(ans[l], (i64)a[l]);
        return;
    }

    int mid = (l + r) >> 1;

    solve(l, mid), solve(mid + 1, r);

    i64 pre = LLONG_MIN, suf = LLONG_MIN;

    for (int i = l; i <= mid; i++) {
        int x = i + L - 1;
        int y = i + R - 1;
        pre = max(pre, ST.query_max(max(x, mid + 1), min(y, r)) - p[i - 1]);
        ans[i] = max(ans[i], pre);
    }

    for (int i = r; i > mid; i--) {
        int x = i - R + 1;
        int y = i - L + 1;
        suf = max(suf, p[i] - ST.query_min(max(x, l) - 1, min(y, mid) - 1));
        ans[i] = max(ans[i], suf);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> L >> R;
    for (int i = 1; i <= n; i++)
        cin >> a[i], p[i] = p[i - 1] + a[i], ans[i] = LLONG_MIN;

    ST.init(n, p);

    solve(1, n);

    for (int i = 1; i <= n; i++)
        cout << ans[i] << ' ';

    fflush(stdout);
    return 0;
}
