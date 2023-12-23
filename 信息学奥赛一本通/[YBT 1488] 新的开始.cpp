#include <tuple>
#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>

using namespace std;
using EDGE = tuple<int, int, int>;

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

struct DisjointSet {
    vector<int> p;
    void init(int n) {
        p.clear();
        p.resize(n + 1);
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }
    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        return p[x] = y, true;
    }
};

int n;
vector<EDGE> edges;
DisjointSet DSU;

int Kruskal() {
    int cnt(0), ans(0);
    for (auto [u, v, w] : edges) {
        if (cnt == n) break;
        u = DSU.find(u);
        v = DSU.find(v);
        if (DSU.merge(u, v))
            cnt += 1, ans += w;
    }
    return ans;
}

int main() {
    n = read();
    DSU.init(n);
    for (int i(1); i <= n; i++)
        edges.emplace_back(0, i, read());

    for (int i(1); i <= n; i++)
        for (int j(1); j <= n; j++)
            if (i >= j) read();
            else edges.emplace_back(i, j, read());

    auto cmp = [&](EDGE a, EDGE b) { return get<2>(a) < get<2>(b); };
    sort(edges.begin(), edges.end(), cmp);

    write(Kruskal()), putchar('\n');
    fflush(stdout);
    return 0;
}
