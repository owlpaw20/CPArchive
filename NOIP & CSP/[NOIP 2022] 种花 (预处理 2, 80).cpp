#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e3 + 10;
const int MOD = 998244353;

char t;
int T, id, n, m, c, f;
long long ans_c, ans_f;
int rght[N][N], down[N][N], up[N][N];
bool map[N][N];

void init() {
    memset(rght, 0, sizeof rght);
    memset(down, 0, sizeof down);
    memset(up, 0, sizeof up);

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

    // 预处理从每个点向上延伸的最远距离
    for (int j = 1; j <= m; j++, len = 0)
        for (int i = 1; i <= n; i++)
            if (!map[i][j])
                up[i][j] = len++;
            else
                up[i][j] = len = 0;
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

        // 只需要枚举 C 的两个角
        for (int i = 3; i <= n; i++)  // 枚举下边的角
            for (int j = 1; j < m; j++) {
                int upable = up[i][j];
                if (!map[i][j] && upable >= 2)
                    for (int k = i - upable; k <= i - 2; k++) {  // 枚举上边的角
                        ans_c = (ans_c + rght[k][j] * rght[i][j] % MOD) % MOD;
                        if (down[i][j] >= 1)  // 枚举 F
                            ans_f =
                                (ans_f + rght[k][j] * rght[i][j] * down[i][j] % MOD) %
                                MOD;
                    }
            }

        cout << c * ans_c % MOD << " " << f * ans_f % MOD << endl;
    }

    fflush(stdout);
    return 0;
}
