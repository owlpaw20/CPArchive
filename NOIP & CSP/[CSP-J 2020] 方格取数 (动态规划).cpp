#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
using i64 = long long;

const int N = 1e3 + 10;
const i64 NINF = 0x8080808080808080;

int n, m;
int grid[N][N];
i64 f[N][N][2];
// f[x][y][0] 表示从左边或上面转移来的最大值
// f[x][y][1] 表示从左边或下面转移来的最大值
// f[x][y][0] = max{f[x-1][y][0], f[x][y-1][0], f[x][y-1][1]}
// f[x][y][1] = max{f[x+1][y][1], f[x][y-1][0], f[x][y-1][1]}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    memset(f, 0x80, sizeof f);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> grid[i][j];
    f[1][1][0] = f[1][1][1] = grid[1][1];
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == 1 && j == 1) continue;
            f[j][i][0] = max({f[j][i - 1][0], f[j][i - 1][1], f[j - 1][i][0]}) + grid[j][i];
        }
        for (int j = n; j > 0; j--) {
            if (i == 1 && j == 1) continue;
            f[j][i][1] = max({f[j][i - 1][0], f[j][i - 1][1], f[j + 1][i][1]}) + grid[j][i];
        }
    }
    cout << f[n][m][0] << endl;
    return 0;
}
