#include <cmath>
#include <cfloat>
#include <vector>
#include <iostream>
#include <algorithm>

#define endl '\n'
#define x first
#define y second

using namespace std;
using flt = double;
using PII = pair<int, int>;

const int N = 150 + 10;
const flt INF = DBL_MAX;

int n;
PII p[N];
flt g[N][N];
int belong[N];
flt pd[N], ad[N];
// pd 即 pasture dist，两个牧区之间的最短路长度的最大值
// ad 即 area diameter，整个牧场的直径，即该牧场内所有 pd 的最大值

flt dist(PII a, PII b) {
    return sqrt((a.x - b.x) * (a.x - b.x) +
                (a.y - b.y) * (a.y - b.y));
}

void DFS(int u, int idx) {
    belong[u] = idx;
    for (int v = 1; v <= n; v++)
        if (!belong[v] && g[u][v] < INF)
            DFS(v, idx);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(6);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> p[i].x >> p[i].y;

    char ch;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            cin >> ch;
            if (ch == '1' || i == j)
                g[i][j] = dist(p[i], p[j]);
            else
                g[i][j] = INF;
        }

    for (int i = 1, idx = 0; i <= n; i++)
        if (!belong[i])
            DFS(i, ++idx);

    for (int v = 1; v <= n; v++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                g[i][j] = min(g[i][j], g[i][v] + g[v][j]);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            if (g[i][j] < INF)
                pd[i] = max(pd[i], g[i][j]);
        ad[belong[i]] = max(ad[belong[i]], pd[i]);
    }

    flt ans = INF;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (belong[i] != belong[j])
                ans = min(ans, max({ad[belong[i]], ad[belong[j]], pd[i] + pd[j] + dist(p[i], p[j])}));

    cout << fixed << ans << endl;
    fflush(stdout);
    return 0;
}
