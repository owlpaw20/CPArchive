#include <cstring>
#include <iostream>

#define endl '\n'

namespace FastIO {
    int read() {
        int x = 0, f = 1;
        char ch = getchar();
        while (ch < '0' || ch > '9') {
            if (ch == '-')
                f = -f;
            ch = getchar();
        }
        while (ch >= '0' && ch <= '9')
            x = x * 10 + ch - 48, ch = getchar();
        return x * f;
    }
    void write(int x) {
        if (x < 0) putchar('-'), x = -x;
        if (x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
} // namespace FastIO
using namespace FastIO;

using namespace std;
using PII = pair<int, int>;

const int N = 2e2 + 5;

// 本题使用匈牙利算法会因为复杂度过大而 TLE
// 但由于玄学原因，当方向数组按以下方向配置的时候，可以 AC
// 当然可能以后如果有 hack 数据就 AC 不了了
const int dx[] = {1, -1, -2, 2, 2, -2, -1, 1};
const int dy[] = {-2, -2, -1, -1, 1, 1, 2, 2};

int n, m;
bool vis[N][N];
PII match[N][N];
bool banned[N][N];

bool Hungarian(PII point) {
    auto [x, y] = point;

    for (int i = 0; i < 8; i++) {
        int tx = x + dx[i];
        int ty = y + dy[i];

        if (tx < 1 || ty < 1 || tx > n || ty > n) continue;
        if (vis[tx][ty] || banned[tx][ty]) continue;

        vis[tx][ty] = true;

        if (match[tx][ty] == PII(0, 0) || Hungarian(match[tx][ty]))
            return match[tx][ty] = point, true;
    }

    return false;
}

int main() {
    n = read(), m = read();

    for (int i = 1; i <= m; i++)
        banned[read()][read()] = true;

    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (!banned[i][j] && (i + j) & 1) {
                memset(vis, 0, sizeof vis);
                ans += Hungarian(PII(i, j));
            }

    write(n * n - m - ans), putchar('\n');
    fflush(stdout);
    return 0;
}
