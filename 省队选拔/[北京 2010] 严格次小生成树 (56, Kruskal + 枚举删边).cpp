#include <tuple>
#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <unordered_set>

#define endl '\n'

using namespace std;
using i64 = long long;
using TUP = tuple<int, int, int>;

const int N = 1e5 + 5;

int n, m;
vector<TUP> edges;

unordered_set<int> used;

namespace UnionFind {
    int fa[N];
    void init(int n) {
        iota(fa, fa + n + 1, 0);
    }
    int find(int x) {
        return x == fa[x] ? x : (fa[x] = find(fa[x]));
    }
    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        return fa[x] = y, true;
    }
} // namespace UnionFind

i64 Kruskal1() {
    i64 ans = 0;
    int cnt = 0;
    UnionFind::init(n);

    for (size_t i = 0; i < edges.size(); i++) {
        if (cnt == n - 1) continue;
        auto [w, u, v] = edges[i];
        if (UnionFind::merge(u, v))
            used.insert(i), ans += w, cnt += 1;
    }

    if (cnt != n - 1) return (1ULL << 63) - 1;
    return ans;
}

i64 Kruskal2(int excluded) {
    i64 ans = 0;
    int cnt = 0;
    UnionFind::init(n);

    for (size_t i = 0; i < edges.size(); i++) {
        if (excluded == (int)i) continue;
        if (cnt == n - 1) continue;
        auto [w, u, v] = edges[i];
        if (UnionFind::merge(u, v))
            ans += w, cnt += 1;
    }

    if (cnt != n - 1) return (1ULL << 63) - 1;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    while (m--) {
        int x, y, z;
        cin >> x >> y >> z;
        if (x == y) continue;
        edges.emplace_back(z, x, y);
    }

    sort(edges.begin(), edges.end());

    int MST = Kruskal1();

    i64 ans = (1ULL << 63) - 1;
    for (int edge : used) {
        i64 x = Kruskal2(edge);
        if (x == MST) continue;
        ans = min(ans, x);
    }

    cout << ans << endl;
    return fflush(stdout), 0;
}
