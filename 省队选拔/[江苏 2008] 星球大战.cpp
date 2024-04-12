#include <vector>
#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;

const int N = 4e5 + 10;
const int M = 2e5 + 10;

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
        int rx = find(x), ry = find(y);
        if (rx != ry) {
            p[rx] = ry;
            return true;
        }
        return false;
    }
};

struct Edge {
    int u, v, id;
    Edge(int x, int y) :
        u(x), v(y), id(0) {}
    bool operator<(const Edge t) const {
        return id < t.id;
    }
};

int n, m, K, cap[N];
vector<Edge> g;
DisjointSet st;
vector<int> ans;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    st.init(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        g.emplace_back(u, v);
    }

    cin >> K;
    for (int i = K; i > 0; i--) {
        int t;
        cin >> t;
        cap[t] = i;
    }

    for (Edge &e : g)
        e.id = max(cap[e.u], cap[e.v]);

    sort(g.begin(), g.end());

    int cnt = n;
    for (int i = 0, j = 0; i <= K; i++) {
        for (; g[j].id == i; j++)
            if (st.merge(g[j].u, g[j].v))
                cnt -= 1;
        ans.push_back(cnt - (K - i));
    }

    for (auto it = ans.rbegin(); it != ans.rend(); it++)
        cout << *it << endl;

    fflush(stdout);
    return 0;
}
