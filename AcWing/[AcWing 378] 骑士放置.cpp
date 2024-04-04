#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;
using PII = pair<int, int>;

const int N = 1e2 + 5;
const int dx[] = {-2, -2, -1, 1, 2, 2, 1, -1};
const int dy[] = {-1, 1, 2, 2, 1, -1, -2, -2};

int n, m, b;
bool banned[N][N];
bool vis[N][N];
PII match[N][N];

bool Hungary(PII point) {
    auto [x, y] = point;

    for (int i = 0; i < 8; i++) {
        int tx = x + dx[i];
        int ty = y + dy[i];

        if (tx < 1 || ty < 1 || tx > n || ty > m) continue;
        if (vis[tx][ty] || banned[tx][ty]) continue;

        vis[tx][ty] = true;

        if (match[tx][ty] == PII(0, 0) || Hungary(match[tx][ty]))
            return match[tx][ty] = point, true;
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> b;

    for (int i = 1; i <= b; i++) {
        int u, v;
        cin >> u >> v;
        banned[u][v] = true;
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (!banned[i][j] && (i + j) & 1) {
                memset(vis, 0, sizeof vis);
                ans += Hungary(PII(i, j));
            }

    cout << n * m - b - ans << endl;

    /*  选出最多的点构成独立集
        等价于：在图中去掉最少的点，使得剩下的点之间没有边
        等价于：用最少的点覆盖所有的边
        因此，从图中去掉二分图的最小点覆盖即可获得二分图的最大独立集。*/

    fflush(stdout);
    return 0;
}
