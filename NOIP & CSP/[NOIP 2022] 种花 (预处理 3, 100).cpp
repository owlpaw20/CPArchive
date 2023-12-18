#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e3 + 10;
const int MOD = 998244353;

char t;
int T, id, n, m, c, f;
long long ans_c, ans_f;
long long rght[N][N], down[N][N], up[N][N], sum[N][N];
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

    /* 计算答案时
     * 需要从 k = i - upable 到 k = i - 2 枚举 right[k][j]
     * 可以通过前缀和来减小复杂度 */

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (!map[i][j]) sum[i][j] = sum[i - 1][j] + rght[i][j];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T >> id;
    while (T--) {
        cin >> n >> m >> c >> f;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                cin >> t, map[i][j] = t - '0';

        init();

        for (int i = 3; i <= n; i++)
            for (int j = 1; j < m; j++) {
                int upable = up[i][j];
                if (!map[i][j] && upable >= 2) {
                    ans_c = (ans_c + (sum[i - 2][j] - sum[i - upable - 1][j]) % MOD * rght[i][j] % MOD) % MOD;
                    if (down[i][j] >= 1)
                        ans_f = (ans_f + (sum[i - 2][j] - sum[i - upable - 1][j]) % MOD * rght[i][j] % MOD * down[i][j] % MOD) % MOD;
                }
            }

        cout << c * ans_c % MOD << " " << f * ans_f % MOD << endl;
    }

    fflush(stdout);
    return 0;
}
