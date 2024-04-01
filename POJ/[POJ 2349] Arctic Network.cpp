#include <cmath>
#include <tuple>
#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>

using namespace std;
using PII = pair<int, int>;
using EDGE = tuple<int, int, double>;

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

int T, n, K;
DisjointSet DSU;
vector<PII> pts;
vector<EDGE> edges;

double calc_dist(int u, int v) {
    auto [x1, y1](pts[u]);
    auto [x2, y2](pts[v]);
    int dx(x1 - x2), dy(y1 - y2);
    return sqrt(dx * dx + dy * dy);
}

double Kruskal() {
    double ans(0);
    int cnt(n);
    for (auto [u, v, w] : edges) {
        if (cnt <= K) break;
        if (DSU.merge(u, v))
            cnt -= 1, ans = w;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(2);

    cin >> T;

    while (T--) {
        cin >> K >> n;
        DSU.init(n);
        edges.clear();
        pts.resize(n + 5);

        for (int i(1); i <= n; i++)
            cin >> pts[i].first >> pts[i].second;

        for (int i(1); i <= n; i++)
            for (int j(i + 1); j <= n; j++)
                edges.emplace_back(i, j, calc_dist(i, j));

        auto cmp = [&](EDGE x, EDGE y) {
            return get<2>(x) < get<2>(y);
        };
        sort(edges.begin(), edges.end(), cmp);

        cout << fixed << Kruskal() << '\n';
    }
    fflush(stdout);
    return 0;
}
