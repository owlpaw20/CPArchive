#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e2 + 5;

int n, m, K;
bool g[N][N];
bool vis[N];
int match[N];

bool Hungary(int u) {
    for (int v = 1; v <= m; v++)
        if (!vis[v] && g[u][v]) {
            vis[v] = true;
            if (!match[v] || Hungary(match[v]))
                return match[v] = u, true;
        }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n, n) {
        cin >> m >> K;

        memset(g, 0, sizeof g);
        memset(match, 0, sizeof match);

        while (K--) {
            int t, u, v;
            cin >> t >> u >> v;
            if (u == 0 || v == 0) continue;
            g[u + 1][v + 1] = true;
        }

        int ans = 0;

        for (int i = 1; i <= n; i++) {
            memset(vis, 0, sizeof vis);
            ans += Hungary(i);
        }

        cout << ans << endl;
    }

    fflush(stdout);
    return 0;
}
