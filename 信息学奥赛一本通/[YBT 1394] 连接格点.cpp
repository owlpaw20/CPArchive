#include <numeric>
#include <iostream>

#define endl '\n'

using namespace std;

namespace UnionFind {
    const int SET_SIZE = 1e6 + 10;
    int fa[SET_SIZE];

    int Find(int x) {
        if (fa[x] == x) return x;
        return fa[x] = Find(fa[x]);
    }

    bool Union(int x, int y) {
        x = Find(x), y = Find(y);
        if (x == y) return false;
        return fa[x] = y, true;
    }
} // namespace UnionFind
using namespace UnionFind;

int n, m;

int H(int x, int y) {
    return (x - 1) * m + y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    iota(fa + 1, fa + n * m + 1, 1);

    int x1, y1, x2, y2;
    while (cin >> x1 >> y1 >> x2 >> y2) {
        int u = H(x1, y1);
        int v = H(x2, y2);
        Union(u, v);
    }

    int ans = 0;

    for (int i = 1; i <= m; i++)
        for (int j = 1; j < n; j++)
            ans += Union(H(j, i), H(j + 1, i));

    for (int i = 1; i <= n; i++)
        for (int j = 1; j < m; j++)
            ans += Union(H(i, j), H(i, j + 1)) << 1;

    cout << ans << endl;
    fflush(stdout);
    return 0;
}
