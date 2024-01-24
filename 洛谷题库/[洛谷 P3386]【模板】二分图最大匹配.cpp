#include <vector>
#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e3;

int n, m, e;
bool vis[N];
int match[N];
vector<int> edges[N];

bool Hungary(int u) {
    for (int v : edges[u])
        if (!vis[v]) {
            vis[v] = true;
            if (!match[v] || Hungary(match[v]))
                return match[v] = u, true;
        }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> e;

    while (e--) {
        int u, v;
        cin >> u >> v;
        edges[u].push_back(v);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        memset(vis, 0, sizeof vis);
        ans += Hungary(i);
    }

    cout << ans << endl;
    fflush(stdout);
    return 0;
}
