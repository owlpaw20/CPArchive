#include <iostream>
#include <algorithm>
using namespace std;

const int N = 4e4 + 40;
const int M = 1e5 + 10;

struct Pair {
    int a, b, c;
} rel[M];

struct DisjointSet {
    int p[N];
    int find(int x) {
        if (p[x] == x) return p[x];
        return p[x] = find(p[x]);
    }
    void merge(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx != ry) p[rx] = ry;
    }
    DisjointSet(int x) {
        for (int i = 1; i < x; i++)
            p[i] = i;
    }
};

int n, m, p[N], ans;

DisjointSet dsu(N);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 1; i <= m; i++)
        cin >> rel[i].a >> rel[i].b >> rel[i].c;

    auto cmp = [&](Pair x, Pair y) { return x.c > y.c; };
    sort(rel + 1, rel + m + 1, cmp);

    for (int i = 1; i <= m; i++) {
        if (dsu.find(rel[i].a) == dsu.find(rel[i].b)) {
            ans = rel[i].c;
            break;
        }
        dsu.merge(rel[i].a + n, rel[i].b);
        dsu.merge(rel[i].b + n, rel[i].a);
    }

    cout << ans << endl;
    return 0;
}
