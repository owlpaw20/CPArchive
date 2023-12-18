#include <cstring>
#include <iostream>

#define endl '\n'
using namespace std;

const int N = 1e3 + 10;
const int MOD = 998244353;

char t;
int T, id, n, m, c, f;
long long ans_c, ans_f;
int cc[N][N], ff[N][N];
bool map[N][N];

void init() {
    memset(cc, 0, sizeof cc);
    memset(ff, 0, sizeof ff);
    ans_c = ans_f = 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T >> id;
    while (T--) {
        init();

        cin >> n >> m >> c >> f;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                cin >> t;
                map[i][j] = t - '0';
            }

        for (int col = 1; col < m; col++)
            for (int nw = 1; nw <= n; nw++)
                for (int sw = nw + 2; sw <= n; sw++) {
                    // 判断 C 的上边是否能向右延伸
                    if (map[nw][col + 1]) continue;
                    if (map[sw][col + 1]) continue;

                    // 判断 C 的竖边能否放得下
                    bool flag = 0;
                    for (int row = nw; row <= sw; row++)
                        if (map[row][col]) {
                            flag = 1;
                            break;
                        }
                    if (flag) continue;

                    // 通过乘法原理计算 C 与 F 的出现次数
                    for (int i = col + 1; i <= m; i++) {  // 延长 C 和 F 的上边
                        if (map[nw][i]) break;
                        for (int j = col + 1; j <= m; j++) {  // 延长 C 和 F 的下边
                            if (map[sw][j]) break;
                            ans_c = (ans_c + 1) % MOD;           // 计算 C 的出现次数
                            for (int k = sw + 1; k <= n; k++) {  // 延长 F 的尾部
                                if (map[k][col]) break;
                                ans_f = (ans_f + 1) % MOD;  // 计算 F 的出现次数
                            }
                        }
                    }
                }

        cout << c * ans_c % MOD << " " << f * ans_f % MOD << endl;
    }

    fflush(stdout);
    return 0;
}
