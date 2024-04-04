#include <cstring>
#include <iostream>
using namespace std;

const int N = 1e3 + 10;
const int MOD = 998244353;

int T, id, n, m, c, f;
long long ans_c, ans_f;
int rght[N][N], down[N][N], up[N][N];
char t;
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
    // 预处理从每一点最多能向上边延伸多远
    for (int j = 1; j <= m; j++, len = 0)
        for (int i = 1; i <= n; i++)
            if (!map[i][j])
                up[i][j] = len++;
            else
                up[i][j] = len = 0;
}

void solve() {
    cin >> n >> m >> c >> f;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> t, map[i][j] = t - '0';

    init();

    // 只需要枚举 C 的两个角了
    for (int i = 3; i <= n; i++) // 枚举 C 左下角的横坐标
        for (int j = 1; j < m; j++) { // 枚举 C 左下角的纵坐标
            int upable = up[i][j]; // 记录 C 的左下角最多能向上延伸的长度
            if (map[i][j] || upable < 2) // 如果当前左下角合法且留给右上角的位置足够大
                continue;

            for (int k = i - upable; k <= i - 2; k++) { // 枚举 C 右上角的横坐标
                ans_c = (ans_c + rght[k][j] * rght[i][j] % MOD) % MOD; // 对 C 进行计数
                if (!down[i][j]) continue; // 判断下方有没有给 F 的出边留空间

                // 对 F 进行计数
                ans_f = (ans_f + rght[k][j] * rght[i][j] * down[i][j] % MOD) % MOD;
            }

            cout << c *ans_c % MOD << " " << f *ans_f % MOD << endl;
        }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T >> id;
    while (T--) solve();
    return 0;
}