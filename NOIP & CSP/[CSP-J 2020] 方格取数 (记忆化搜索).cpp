#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
using lng = long long;

const int N = 1e3 + 10;
const lng NINF = 0x8080808080808080;

int n, m;
int grid[N][N];
lng f[N][N][2];
// f[x][y][0] 表示从左边或上面转移来的最大值
// f[x][y][1] 表示从左边或下面转移来的最大值
// f[x][y][0] = max{f[x-1][y][0], f[x][y-1][0], f[x][y-1][1]}
// f[x][y][1] = max{f[x+1][y][1], f[x][y-1][0], f[x][y-1][1]}

lng DFS(int x, int y, int from) {
    if (x < 1 || y < 1 || x > n || y > m) return NINF;
    if (f[x][y][from] != NINF) return f[x][y][from];
    if (from == 0)
        f[x][y][0] = max({DFS(x - 1, y, 0), DFS(x, y - 1, 0), DFS(x, y - 1, 1)}) + grid[x][y];
    else if (from == 1)
        f[x][y][1] = max({DFS(x + 1, y, 1), DFS(x, y - 1, 0), DFS(x, y - 1, 1)}) + grid[x][y];
    return f[x][y][from];
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    memset(f, 0x80, sizeof f);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> grid[i][j];
    f[1][1][0] = f[1][1][1] = grid[1][1];
    cout << DFS(n, m, 0) << endl;
    return 0;
}
