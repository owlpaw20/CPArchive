#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
using PII = pair<int, int>;

struct DisjointSet {
    vector<int> p;
    void init(int n) {
        p.resize(n);
        for (int i = 0; i < n; i++)
            p[i] = i;
    }
    int find(int x) {
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }
    void merge(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx != ry) p[rx] = ry;
    }
};

struct Edge {
    int u, v, w1, w2, id;
};

int n, K, m;
vector<Edge> g;
vector<PII> road;
DisjointSet dsu;

void Kruskal(int which, int& ans) {
    for (Edge e : g) {
        if (which == 1 && road.size() == K) break;
        if (which == 2 && road.size() == n - 1) break;
        int u = dsu.find(e.u);
        int v = dsu.find(e.v);
        if (u != v) {
            ans = max(ans, (which == 1 ? e.w1 : e.w2));
            road.emplace_back(e.id, which);
            dsu.merge(e.u, e.v);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> K >> m;
    dsu.init(n + 10);
    for (int i = 1; i < m; i++) {
        int u, v, w1, w2;
        cin >> u >> v >> w1 >> w2;
        g.push_back((Edge){u, v, w1, w2, i});
    }

    auto cmp1 = [&](Edge x, Edge y) { return x.w1 < y.w1; };
    auto cmp2 = [&](Edge x, Edge y) { return x.w2 < y.w2; };
    auto cmp3 = [&](PII x, PII y) { return x.first < y.first; };

    int ans = 0;
    sort(g.begin(), g.end(), cmp1);
    Kruskal(1, ans);
    sort(g.begin(), g.end(), cmp2);
    Kruskal(2, ans);

    cout << ans << endl;

    sort(road.begin(), road.end(), cmp3);
    for (PII ans : road) {
        auto [t, p] = ans;
        cout << t << " " << p << endl;
    }
    return 0;
}
