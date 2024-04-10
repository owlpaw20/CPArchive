#include <cstring>
#include <iostream>
#include <algorithm>

#define endl '\n'

const int MAX_M = 3e2 + 5;
const int MAX_F = 3e2 + 5;
const int MAX_R = 3e2 + 5;
const int INF = 0x3F3F3F3F;

int M, F, R, C, cap[MAX_R], prc[MAX_R];
int f[MAX_R][MAX_M][MAX_F]; // 无夫妻
int g[MAX_R][MAX_M][MAX_F]; // 有一组夫妻

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    memset(f, 0x3F, sizeof f);
    memset(g, 0x3F, sizeof g);

    std::cin >> M >> F >> R >> C;
    for (int i = 1; i <= R; ++i)
        std::cin >> cap[i] >> prc[i];

    f[0][0][0] = 0;

    for (int i = 1; i <= R; ++i)
        for (int j = M; ~j; --j)
            for (int k = F; ~k; --k) {
                f[i][j][k] = f[i - 1][j][k];

                if (cap[i] >= 2 && j && k) // 如果能够组成一组夫妻，则从无夫妻状态进行转移
                    g[i][j][k] = std::min(g[i - 1][j][k], f[i - 1][j - 1][k - 1] + prc[i]);

                // 对于同性入住，枚举当前房间所有可能的入住人数 t
                for (int t = 1; t <= cap[i]; ++t) {
                    if (j >= t) { // 如果剩余男性人数大于 t，则转移
                        f[i][j][k] = std::min(f[i][j][k], f[i - 1][j - t][k] + prc[i]);
                        g[i][j][k] = std::min(g[i][j][k], g[i - 1][j - t][k] + prc[i]);
                    }
                    if (k >= t) { // 如果剩余女性人数大于 t，则转移
                        f[i][j][k] = std::min(f[i][j][k], f[i - 1][j][k - t] + prc[i]);
                        g[i][j][k] = std::min(g[i][j][k], g[i - 1][j][k - t] + prc[i]);
                    }
                }
            }

    int ans = std::min(f[R][M][F], g[R][M][F]);
    std::cout << (ans == INF ? "Impossible" : std::to_string(ans)) << endl;
    return fflush(stdout), 0;
}
