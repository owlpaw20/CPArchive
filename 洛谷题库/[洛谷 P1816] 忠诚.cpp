#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

const int INF = 0x3f3f3f3f;

int n, m;

struct SparseTable {
    using VI = vector<int>;
    using VII = vector<VI>;
    VII ST;
    void prep(VI v, int x) {
        for (int i = 1; i <= x; i++)
            ST[i][0] = v[i];
        int lmt = ceil(log2(x)) + 1;
        for (int j = 1; j <= lmt; j++)
            for (int i = 1; i + (1 << j) - 1 <= x; i++)
                ST[i][j] = min(ST[i][j - 1], ST[i + (1 << (j - 1))][j - 1]);
    }
    int query(int l, int r) {
        int t = log2(r - l + 1);
        return min(ST[l][t], ST[r - (1 << t) + 1][t]);
    }
    SparseTable(VI v, int x) {
        int lmt = ceil(log2(x)) + 1;
        ST.resize(x + 1, VI(lmt, INF));
        prep(v, x);
    }
};

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    SparseTable ST(a, n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        cout << ST.query(a, b) << " ";
    }
    cout << endl;
    return 0;
}
