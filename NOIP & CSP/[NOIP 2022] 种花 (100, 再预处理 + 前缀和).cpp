#include <cstring>
#include <iostream>
using namespace std;

const int N = 1e3 + 10;
const int MOD = 998244353;

int T, id, n, m, c, f;
long long ans_c, ans_f, sum[N][N];
int rght[N][N], down[N][N], up[N][N];
char t;
bool map[N][N];

void init() {
    memset(rght, 0, sizeof rght);
    memset(down, 0, sizeof down);
    memset(up, 0, sizeof up);
    memset(sum, 0, sizeof sum);
    ans_c = ans_f = 0;

    int len = 0;
    for (int i = 1; i <= n; i++, len = 0)
        for (int j = m; j >= 1; j--)
            if (!map[i][j])
                rght[i][j] = len++;
            else
                rght[i][j] = len = 0;

    len = 0;
    for (int j = 1; j <= m; j++, len = 0)
        for (int i = n; i >= 1; i--)
            if (!map[i][j])
                down[i][j] = len++;
            else
                down[i][j] = len = 0;

    len = 0;
    for (int j = 1; j <= m; j++, len = 0)
        for (int i = 1; i <= n; i++)
            if (!map[i][j])
                up[i][j] = len++;
            else
                up[i][j] = len = 0;

    /*  对每个点能够向右延伸的最大距离求前缀和

        计算答案时，需要从 rght[i - upable][j]
        一直累加到 rght[i - 2][j]，非常浪费时间
        可以使用前缀和在常数复杂度内求出上述区间的和
        这样一来算法的总复杂度就降到了O(n^2) */

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (!map[i][j]) sum[i][j] = sum[i - 1][j] + rght[i][j];
}

long long pre(int l, int r, int j) {
    return sum[r][j] - sum[l - 1][j];
}

void solve() {
    cin >> n >> m >> c >> f;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> t, map[i][j] = t - '0';

    init();

    for (int i = 3; i <= n; i++)
        for (int j = 1; j < m; j++) {
            int upable = up[i][j];
            if (map[i][j] || upable < 2) continue;
            ans_c = (ans_c + pre(i - upable, i - 2, j) % MOD * rght[i][j] % MOD) % MOD;
            if (down[i][j] < 1) continue;
            ans_f = (ans_f + pre(i - upable, i - 2, j) % MOD * rght[i][j] % MOD * down[i][j] % MOD) % MOD;
        }
    cout << c * ans_c % MOD << " " << f * ans_f % MOD << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T >> id;
    while (T--) solve();
    return 0;
}