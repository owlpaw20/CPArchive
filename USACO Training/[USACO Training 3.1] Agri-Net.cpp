#include <vector>
#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;

struct Edge {
    int u, v, w;

    Edge() {}

    Edge(int _u, int _v, int _w)
        : u(_u), v(_v), w(_w) {}

    bool operator<(const Edge &t) const {
        return w < t.w;
    }
};

struct DisjointSet {
    vector<int> p;

    void init(int n) {
        p.clear();
        p.resize(n + 1);
        for (int i = 1; i <= n; i++)
            p[i] = i;
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
vector<Edge> edges;
DisjointSet DSU;

int Kruskal() {
    int cnt = 0, ans = 0;
    for (Edge e : edges) {
        if (cnt == n - 1) break;
        auto [u, v, w] = e;
        u = DSU.find(u);
        v = DSU.find(v);
        if (DSU.merge(u, v))
            ans += w, cnt += 1;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    DSU.init(n);
    for (int i = 1; i <= n; i++)
        for (int j = 1, t; j <= n; j++) {
            cin >> t;
            if (i >= j) continue;
            edges.emplace_back(i, j, t);
        }

    sort(edges.begin(), edges.end());

    cout << Kruskal() << endl;
    fflush(stdout);
    return 0;
}
