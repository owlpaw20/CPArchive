#pragma GCC optimize("O2,unroll-loops")
#include <iostream>
#define endl '\n'

using namespace std;

const int N = 10;
const int dx[] = {-2, -2, -1, 1, 2, 2, 1, -1};
const int dy[] = {-1, 1, 2, 2, 1, -1, -2, -2};

int T, n, m, ans;
bool vis[N][N];

void DFS(int x, int y, int cnt) {
    if (cnt == n * m)
        return (void)(ans += 1);

    for (int i = 0; i < 8; i++) {
        int tx = x + dx[i], ty = y + dy[i];
        if (tx < 0 || ty < 0 || tx >= n || ty >= m) continue;
        if (vis[tx][ty]) continue;
        vis[tx][ty] = true;
        DFS(tx, ty, cnt + 1);
        vis[tx][ty] = false;
    }
}

void solve() {
    int x, y;
    cin >> n >> m >> x >> y;

    ans = 0;
    vis[x][y] = true;
    DFS(x, y, 1);
    vis[x][y] = false;

    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) solve();

    fflush(stdout);
    return 0;
}
