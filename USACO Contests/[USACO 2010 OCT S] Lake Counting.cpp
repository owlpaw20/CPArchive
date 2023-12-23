#include <iostream>
using namespace std;

const int N = 1e3 + 10;
const int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
const int dy[] = {-1, -1, 0, 1, 1, -1, 0, 1};

int n, m;
char g[N][N];
bool vis[N][N];

void DFS(int x, int y) {
    for (int i = 0; i < 8; i++) {
        int tx = x + dx[i];
        int ty = y + dy[i];
        if (g[tx][ty] != 'W' || vis[tx][ty]) continue;
        if (tx > 0 && ty > 0 && tx <= n && ty <= m) {
            vis[tx][ty] = true;
            DFS(tx, ty);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> g[i][j];

    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (g[i][j] == 'W' && !vis[i][j])
                DFS(i, j), ans++;

    cout << ans << endl;
    return 0;
}
