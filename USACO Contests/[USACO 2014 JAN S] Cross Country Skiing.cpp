#include <queue>
#include <climits>
#include <cstring>
#include <iostream>
#define endl '\n'

using namespace std;
using PII = pair<int, int>;

const int N = 5e2 + 10;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

int n, m, sx, sy, g[N][N];
bool vis[N][N], crucial[N][N];

bool check(int mid) {
    memset(vis, false, sizeof vis);

    queue<PII> q;
    vis[sx][sy] = true;
    q.emplace(sx, sy);

    while (!q.empty()) {
        auto [x, y] = q.front();
        for (int i = 0, tx, ty; i < 4; i++) {
            tx = x + dx[i], ty = y + dy[i];
            if (tx < 1 || ty < 1 || tx > n || ty > m) continue;
            if (!vis[tx][ty] && abs(g[tx][ty] - g[x][y]) <= mid) {
                vis[tx][ty] = true;
                q.emplace(tx, ty);
            }
        }
        q.pop();
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (crucial[i][j] && !vis[i][j])
                return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> g[i][j];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            cin >> crucial[i][j];
            if (crucial[i][j])
                sx = i, sy = j;
        }

    int l = 0, r = 1e9;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(mid))
            r = mid;
        else
            l = mid + 1;
    }

    cout << r << endl;
    fflush(stdout);
    return 0;
}
