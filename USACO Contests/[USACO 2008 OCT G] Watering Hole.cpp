#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;
using VEC = vector<int>;

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
} // namespace FastIO
using namespace FastIO;

struct Edge {
    int fr, to, wt;
    Edge() {}
    Edge(int x, int y, int z) : fr(x), to(y), wt(z) {}
    bool operator<(const Edge& t) const {
        return wt < t.wt;
    }
};

struct DisjointSet {
    vector<int> f;

    void init(int n) {
        f.clear();
        f.resize(n + 5);
        for (int i = 1; i <= n; i++) f[i] = i;
    }

    int find(int x) {
        if (f[x] == x) return x;
        return f[x] = find(f[x]);
    }

    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        return (f[x] = y);
    }

    DisjointSet() {}
    DisjointSet(int n) {
        init(n);
    }
};

int n;

vector<int> w;
DisjointSet DSU;
vector<Edge> edge;

int Kruskal() {
    int cnt = 0, ans = 0;
    for (auto [fr, to, wt] : edge) {
        fr = DSU.find(fr);
        to = DSU.find(to);
        if (DSU.merge(fr, to))
            ans += wt, cnt += 1;
    }
    return ans;
}

int main() {
    n = read();

    DSU.init(n + 1);
    w.resize(n + 5);

    for (int i = 1; i <= n; i++) w[i] = read();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i != j) edge.emplace_back(i, j, read());
            else read();

    for (int i = 1; i <= n; i++) {
        edge.emplace_back(i, n + 1, w[i]);
        edge.emplace_back(n + 1, i, w[i]);
    }

    sort(edge.begin(), edge.end());
    write(Kruskal()), putchar('\n');

    fflush(stdout);
    return 0;
}
