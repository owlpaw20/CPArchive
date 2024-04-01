#include <vector>
#include <iostream>

#define endl '\n'
using namespace std;

struct DisjointSet {
    vector<int> p;
    void init(int n) {
        p.resize(n + 5);
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
        p[x] = y;
        return true;
    }
    DisjointSet() {}
    DisjointSet(int n) {
        init(n);
    }
};

int n, m;
DisjointSet dsu;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    dsu.init(n * 2);

    while (m--) {
        char opt;
        int p, q;
        cin >> opt >> p >> q;

        if (opt == 'F')
            dsu.merge(p, q);
        else if (opt == 'E') {
            dsu.merge(p + n, q); // 注意连边的方向
            dsu.merge(q + n, p); // p + n --> q 表示 p 的敌人是 q
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (dsu.p[i] == i)
            ans += 1;

    cout << ans << endl;
    fflush(stdout);
    return 0;
}
