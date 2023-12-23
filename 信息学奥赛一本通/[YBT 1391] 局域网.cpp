#include <tuple>
#include <vector>
#include <iostream>
#include <algorithm>
#define endl '\n'
using namespace std;
using EDGE = tuple<int, int, int>;

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

int n, m;
vector<EDGE> edges;
DisjointSet DSU;

int Kruskal() {
    int cnt = 0, ans = 0;
    for (EDGE e : edges) {
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

    cin >> n >> m;
    DSU.init(n);

    int wt_sum = 0;
    for (int i = 1, a, b, c; i <= m; i++) {
        cin >> a >> b >> c;
        edges.emplace_back(a, b, c);
        wt_sum += c;
    }

    auto cmp = [](EDGE x, EDGE y) { return get<2>(x) < get<2>(y); };
    sort(edges.begin(), edges.end(), cmp);

    cout << wt_sum - Kruskal() << endl;
    fflush(stdout);
    return 0;
}
