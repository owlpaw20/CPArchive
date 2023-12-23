// 本题于 [AcWing 1098] 提交

#include <iostream>
using namespace std;

const int N = 60;
const int dx[] = {0, -1, 0, 1};
const int dy[] = {-1, 0, 1, 0};

int n, m, cnt, mx, rooms;
int g[N][N];
bool vis[N][N];
// 0 ~ 3: W N E S

void DFS(int x, int y) {
    vis[x][y] = true;
    for (int i = 0; i < 4; i++) {
        int tx = x + dx[i];
        int ty = y + dy[i];
        if (vis[tx][ty] || (g[x][y] >> i) & 1) continue;
        if (tx > 0 && ty > 0 && tx <= n && ty <= m) {
            DFS(tx, ty);
            cnt++;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    int t;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> g[i][j];

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (!vis[i][j]) {
                cnt = 1;
                DFS(i, j);
                rooms++, mx = max(mx, cnt);
            }

    cout << rooms << endl;
    cout << mx << endl;
    return 0;
}
