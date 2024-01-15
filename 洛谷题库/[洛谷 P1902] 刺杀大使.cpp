#include <queue>
#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;
using PII = pair<int, int>;

const int N = 1e3 + 10;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

int n, m;
int dmg[N][N];
bool vis[N][N];

bool check(int lmt) {
    memset(vis, 0, sizeof vis);

    queue<PII> q;
    q.emplace(1, 1);

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (vis[x][y]) continue;
        vis[x][y] = true;

        if (x == n) return true;

        for (int i = 0; i < 4; i++) {
            int tx = x + dx[i], ty = y + dy[i];
            if (tx < 1 || tx > n || ty < 1 || ty > m) continue;
            if (vis[tx][ty] || dmg[tx][ty] > lmt) continue;
            q.emplace(tx, ty);
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    int maxdmg = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> dmg[i][j], maxdmg = max(maxdmg, dmg[i][j]);

    int l = 0, r = maxdmg;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }

    cout << r << endl;
    fflush(stdout);
    return 0;
}
