#include <cstring>
#include <iostream>
using namespace std;
using Long = long long;

const int N = 1e5 + 10;
const int M = 2e5 + 10;

int n, m, idx, f[N];
int ed[M], nx[M], head[N];
int indeg[N], outdeg[N];
Long ans;

void connect(int u, int v) {
    outdeg[u]++, indeg[v]++;
    ed[idx] = v;
    nx[idx] = head[u];
    head[u] = idx++;
}

Long MDFS(int node) {
    if (f[node]) return f[node];
    Long ret = 0;
    if (outdeg[node] == 0 && indeg[node] != 0) ret++;
    for (int i = head[node]; ~i; i = nx[i]) {
        int j = ed[i];
        ret += MDFS(j);
    }
    return f[node] = ret;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    memset(head, -1, sizeof head);
    cin >> n >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        connect(u, v);
    }
    for (int i = 1; i <= n; i++)
        if (indeg[i] == 0)
            ans += MDFS(i);
    cout << ans << endl;
    return 0;
}
