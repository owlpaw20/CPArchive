#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;
using PII = pair<int, int>;

const int N = 1e2 + 5;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

int n, m;
bool a[N][N];
bool vis[N][N];
PII match[N][N];

bool Hungary(PII point) {
    auto [x, y] = point;

    for (int i = 0; i < 4; i++) {
        int tx = x + dx[i];
        int ty = y + dy[i];

        if (tx < 1 || tx > n || ty < 1 || ty > n) continue;
        if (a[tx][ty]) continue;
        if (vis[tx][ty]) continue;

        vis[tx][ty] = true;

        if (match[tx][ty] == PII(0, 0) || Hungary(match[tx][ty]))
            return match[tx][ty] = PII(x, y), true;
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    while (m--) {
        int x, y;
        cin >> x >> y;
        a[x][y] = true;
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (!a[i][j] && (i + j) & 1) {
                memset(vis, 0, sizeof vis);
                ans += Hungary(PII(i, j));
            }

    cout << ans << endl;
    fflush(stdout);
    return 0;
}
