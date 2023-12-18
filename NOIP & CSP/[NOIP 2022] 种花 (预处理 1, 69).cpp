#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e3 + 10;
const int MOD = 998244353;

char t;
int T, id, n, m, c, f;
long long ans_c, ans_f;
int rght[N][N], down[N][N];
bool map[N][N];

void init() {
    memset(rght, 0, sizeof rght);
    memset(down, 0, sizeof down);
    ans_c = ans_f = 0;

    int len = 0;

    // 预处理从每个点出发向右可延伸的最远距离
    for (int i = 1; i <= n; i++, len = 0)
        for (int j = m; j >= 1; j--)
            if (!map[i][j]) rght[i][j] = len++;
            else rght[i][j] = 0, len = 0;

    len = 0;

    // 预处理从每个点出发向下延伸的最远距离
    for (int j = 1; j <= m; j++, len = 0)
        for (int i = n; i >= 1; i--)
            if (!map[i][j]) down[i][j] = len++;
            else down[i][j] = 0, len = 0;
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

        for (int j = 1; j < m; j++)
            for (int nw = 1; nw <= n; nw++)
                for (int sw = nw + 2; sw <= n; sw++) {
                    bool flag = 0;
                    for (int i = nw; i <= sw; i++)
                        if (map[i][j]) {
                            flag = 1;
                            break;
                        }
                    if (flag) continue;

                    // 计算 C 与 F 的出现次数
                    ans_c = (ans_c + rght[nw][j] * rght[sw][j] % MOD) % MOD;
                    ans_f = (ans_f + rght[nw][j] * rght[sw][j] * down[sw][j] % MOD) % MOD;
                }

        cout << c * ans_c % MOD << " " << f * ans_f % MOD << endl;
    }

    fflush(stdout);
    return 0;
}
