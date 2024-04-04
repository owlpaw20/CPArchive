#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 3e2 + 10;
const int M = 1e5 + 10;
struct Edge {
    int u, v, w;
    inline bool operator<(const Edge &other) const {
        return w < other.w;
    }
};

int n, m, tot, p[N];
Edge f[M];

int find_set(int v) {
    if (v == p[v])
        return v;
    return p[v] = find_set(p[v]);
}

int Kruskal() {
    int cnt = 0, ans = -1;
    for (int i = 1; i <= m; i++) {
        if (cnt == n - 1)
            break;
        int u = find_set(f[i].u);
        int v = find_set(f[i].v);
        if (u == v)
            continue;
        p[u] = v;
        ans = max(ans, f[i].w);
        cnt++;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        p[i] = i;
    for (int i = 1; i <= m; i++)
        cin >> f[i].u >> f[i].v >> f[i].w;
    sort(f + 1, f + m + 1);
    int ans = Kruskal();
    cout << n - 1 << " " << ans << endl;
    return 0;
}
