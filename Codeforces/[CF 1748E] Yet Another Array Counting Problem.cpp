#pragma GCC optimize("O2,unroll-loops")

#include <vector>
#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;

const int N = 2e5 + 5;
const int MOD = 1e9 + 7;

int n, m, a[N];
vector<i64> f[N], g[N];

struct SparseTable {
    int tb[N][20];

    int log2(int x) {
        int exp = 0;
        while (x >>= 1)
            exp += 1;
        return exp;
    }

    void prep() {
        int lmt = log2(n);
        for (int i = 1; i <= n; i++) {
            tb[i][0] = i;
            f[i].assign(m + 1, 0);
            g[i].assign(m + 1, 0);
        }
        for (int j = 1; j <= lmt; j++)
            for (int i = 1, x, y; i + (1 << j) - 1 <= n; i++)
                if (a[x = tb[i][j - 1]] >= a[y = tb[i + (1 << (j - 1))][j - 1]])
                    tb[i][j] = x;
                else
                    tb[i][j] = y;
    }

    int max(int l, int r) {
        int t = log2(r - l + 1), x, y;
        if (a[x = tb[l][t]] >= a[y = tb[r - (1 << t) + 1][t]]) return x;
        return y;
    }
} ST;

int divide_and_conquer(int l, int r) {
    if (l > r) return -1;

    int mid = ST.max(l, r);
    int lc = divide_and_conquer(l, mid - 1);
    int rc = divide_and_conquer(mid + 1, r);

    for (int i = 1; i <= m; i++) {
        if (lc != -1 && i == 1)
            f[mid][1] = 0;
        else
            f[mid][i] = (lc != -1 ? g[lc][i - 1] : 1LL) * (rc != -1 ? g[rc][i] : 1LL) % MOD;
        g[mid][i] = (g[mid][i - 1] + f[mid][i]) % MOD;
    }

    return mid;
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    ST.prep();

    int mid = divide_and_conquer(1, n);
    cout << g[mid][m] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) solve();

    return fflush(stdout), 0;
}
