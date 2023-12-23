#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

const int INF = 0x3f3f3f3f;

struct SparseTable {
    using VI = vector<int>;
    using VII = vector<VI>;
    VII ST_max, ST_min;
    void prep_max(int x, VI v) {
        for (int i = 1; i <= x; i++)
            ST_max[i][0] = v[i];
        int lmt = ceil(log2(x)) + 1;
        for (int j = 1; j <= lmt; j++)
            for (int i = 1; i + (1 << j) - 1 <= x; i++)
                ST_max[i][j] = max(ST_max[i][j - 1], ST_max[i + (1 << (j - 1))][j - 1]);
    }
    void prep_min(int x, VI v) {
        for (int i = 1; i <= x; i++)
            ST_min[i][0] = v[i];
        int lmt = ceil(log2(x)) + 1;
        for (int j = 1; j <= lmt; j++)
            for (int i = 1; i + (1 << j) - 1 <= x; i++)
                ST_min[i][j] = min(ST_min[i][j - 1], ST_min[i + (1 << (j - 1))][j - 1]);
    }
    int query_max(int l, int r) {
        int t = log2(r - l + 1);
        return max(ST_max[l][t], ST_max[r - (1 << t) + 1][t]);
    }
    int query_min(int l, int r) {
        int t = log2(r - l + 1);
        return min(ST_min[l][t], ST_min[r - (1 << t) + 1][t]);
    }
    SparseTable(int x, VI v) {
        int lmt = ceil(log2(x)) + 1;
        ST_max.resize(x + 1, VI(lmt, 0));
        ST_min.resize(x + 1, VI(lmt, INF));
        prep_max(x, v), prep_min(x, v);
    }
};

int n, q;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    SparseTable ST(n, a);
    while (q--) {
        int a, b;
        cin >> a >> b;
        int mx = ST.query_max(a, b);
        int mn = ST.query_min(a, b);
        cout << mx - mn << endl;
    }
    return 0;
}
