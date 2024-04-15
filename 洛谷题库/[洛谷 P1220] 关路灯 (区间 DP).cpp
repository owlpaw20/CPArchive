#include <cstring>
#include <iostream>

#define endl '\n'

const int MAX_N = 55;

int N, C;
int pos[MAX_N], power[MAX_N];
int psum[MAX_N];

int f[MAX_N][MAX_N];  // 老张位于区间 [i, j] 的左端点时的最优解
int g[MAX_N][MAX_N];  // 老张位于区间 [i, j] 的右端点时的最优解

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> N >> C;
    for (int i = 1; i <= N; ++i) {
        std::cin >> pos[i] >> power[i];
        psum[i] = psum[i - 1] + power[i];
    }

    memset(g, 0x3F, sizeof g);
    memset(f, 0x3F, sizeof f);

    f[C][C] = g[C][C] = 0;

    auto intvl = [&](const int l, const int r) -> int { return pos[r] - pos[l]; };

    for (int len = 2; len <= N; ++len)
        for (int i = 1, j = len, psum_1, psum_2; j <= N; ++i, ++j) {
            psum_1 = psum[N] - psum[j] + psum[i];          // [1, i + 1) 和 (j, N] 上的路灯还没有关闭
            psum_2 = psum[N] - psum[j - 1] + psum[i - 1];  // [1, i) 和 (j - 1, N] 上的路灯还没有关闭

            // 如果老张最后停在左端点 i 处，则他要么是关闭完 j 路灯后折返回来关 i 路灯的，要么是关闭完第 i + 1 路灯后继续前进来关灯的
            f[i][j] = std::min(f[i + 1][j] + intvl(i, i + 1) * psum_1, g[i + 1][j] + intvl(i, j) * psum_1);

            // 如果老张最后停在右端点 j 处，则他要么是关闭完 i 路灯后折返回来关 j 路灯的，要么是关闭完第 j - 1 路灯后继续前进来关灯的
            g[i][j] = std::min(g[i][j - 1] + intvl(j - 1, j) * psum_2, f[i][j - 1] + intvl(i, j) * psum_2);
        }

    std::cout << std::min(f[1][N], g[1][N]) << endl;
    return fflush(stdout), 0;
}
