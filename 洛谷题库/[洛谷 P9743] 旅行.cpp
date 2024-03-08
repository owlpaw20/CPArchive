#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;

const int N = 50;
const int M = 95;
const int MOD = 998244353;

int n, m, K;
int a[N][N], b[N][N];
i64 f[2][N][N][N][M];
// f[x][y][l][z][p] 表示从 (1, 1) 到 (x, y) 时购买 l 张 L 公司票、z 张 Z 公司票且有 p 元钱的方案数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> K;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> b[i][j];

    f[1][1][0][0][K] = 1;

    int cur = 1;
    for (int x = 1; x <= n; x++, cur ^= 1) {
        for (int y = 1; y <= m; y++) {
            for (int l = 0; l < n; l++)
                for (int z = 0; z < m; z++)
                    for (int p = 0; p <= K; p++) {
                        i64& st = f[cur][y][l][z][p];

                        // 从当前位置的上方转移到当前位置，用一张 L 票
                        if (x > 1) st += f[cur ^ 1][y][l + 1][z][p];

                        // 从当前位置的左方转移到当前位置，用一张 Z 票
                        if (y > 1) st += f[cur][y - 1][l][z + 1][p];

                        // 在当前位置购买了一张 L 票而转移到当前状态
                        if (l > 0 && p + a[x][y] <= K)
                            st += f[cur][y][l - 1][z][p + a[x][y]];

                        // 在当前位置购买了一张 Z 票而转移到当前状态
                        if (z > 0 && p + b[x][y] <= K)
                            st += f[cur][y][l][z - 1][p + b[x][y]];

                        // 减去重复购买的情况
                        if (l > 0 && z > 0 && p + a[x][y] + b[x][y] <= K)
                            st += MOD - f[cur][y][l - 1][z - 1][p + a[x][y] + b[x][y]];

                        st %= MOD;  // 卡常
                    }

            cout << f[cur][y][0][0][0] << ' ';
        }

        cout << endl;

        // 滚动数组清零
        for (int y = 1; y <= m; y++)
            for (int l = 0; l <= n; l++)
                for (int z = 0; z <= m; z++)
                    for (int p = 0; p <= K; p++)
                        f[cur ^ 1][y][l][z][p] = 0;
    }

    fflush(stdout);
    return 0;
}
