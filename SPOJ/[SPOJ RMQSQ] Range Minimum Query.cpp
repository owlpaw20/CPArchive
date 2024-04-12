#include <cmath>
#include <cstdio>
#include <vector>
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

struct SparseTable {
    using VI = vector<int>;
    using VVI = vector<VI>;
    VVI ST;
    int lmt;
    void prep(int x, VI v) {
        int lmt = ceil(log2(x)) + 1;
        for (int i = 1; i <= x; i++)
            ST[i][0] = v[i];
        for (int j = 1; j <= lmt; j++)
            for (int i = 1; i + (1 << j) - 1 <= x; i++)
                ST[i][j] = min(ST[i][j - 1], ST[i + (1 << (j - 1))][j - 1]);
    }
    int query(int l, int r) {
        int t = log2(r - l + 1);
        return min(ST[l][t], ST[r - (1 << t) + 1][t]);
    }
    SparseTable(int x, VI v) {
        int lmt = ceil(log2(x)) + 1;
        ST.resize(x + 1, VI(lmt, 0x3F));
        prep(x, v);
    }
};

int n, m;

int main() {
    n = read();
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        a[i] = read();
    SparseTable ST(n, a);
    m = read();
    while (m--) {
        int l, r;
        l = read(), r = read();
        write(ST.query(l + 1, r + 1)), putchar('\n');
    }
    return 0;
}
