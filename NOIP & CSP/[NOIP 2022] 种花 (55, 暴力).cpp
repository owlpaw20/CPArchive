#include <cstring>
#include <iostream>
using namespace std;

const int N = 1e3 + 10;
const int MOD = 998244353;

int T, id, n, m, c, f;
long long ans_c, ans_f;
int cc[N][N], ff[N][N];
char t;
bool map[N][N];

void solve() {
    memset(cc, 0, sizeof cc);
    memset(ff, 0, sizeof ff);
    ans_c = ans_f = 0;

    cin >> n >> m >> c >> f;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> t, map[i][j] = t - '0';

    for (int col = 1; col < m; col++)
        for (int nw = 1; nw <= n; nw++)
            for (int sw = nw + 2; sw <= n; sw++) {
                // 判断 C 的上下两边是否可以延伸
                if (map[nw][col + 1]) continue;
                if (map[sw][col + 1]) continue;

                // 判断 C 的竖边是否可以放在本列的 [nw, sw] 纵坐标区间内
                bool flag = 0;
                for (int row = nw; row <= sw; row++)
                    if (map[row][col]) {
                        flag = 1;
                        break;
                    }
                if (flag) continue;

                // 对 C 与 F 计数
                for (int i = col + 1; i <= m; i++) {  // 向右延伸 C 的上边
                    if (map[nw][i]) break;            // 直到被阻挡

                    for (int j = col + 1; j <= m; j++) {  // 向右延伸 C 的下边
                        if (map[sw][j]) break;            // 直到被阻挡
                        ans_c = (ans_c + 1) % MOD;        // 对 C 计数

                        for (int k = sw + 1; k <= n; k++) {  // 向下延伸 F 的出边
                            if (map[k][col]) break;          // 直到被阻挡
                            ans_f = (ans_f + 1) % MOD;       // 对 F 计数
                        }
                    }
                }
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
