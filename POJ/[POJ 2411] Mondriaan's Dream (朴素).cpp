#include <iostream>
using namespace std;
using i64 = long long;

const int N = 12;
const int M = 1 << 12;

int n, m;
i64 f[N][M];
bool state[M];

void solve(const int &n, const int &m) {
    for (int i = 0; i < (1 << m); i++) {
        int zero_cnt = 0; // 连续的 0 的个数
        bool is_even = true; // 某个状态如果有奇数个连续的零，说明不合法
        for (int j = 0; j < m; j++) {
            if ((i >> j) & 1) { // 如果当前位为 1
                if (zero_cnt & 1) { // 且前面有奇数个连续的 0
                    is_even = false; // 则不合法，进行标记
                    break;
                }
                zero_cnt = 0; // 因为当前位为 1，则重置 0 的计数器
            } else
                zero_cnt += 1; // 如果当前为为 0，则计数一次
        }
        if (zero_cnt & 1) is_even = false;
        state[i] = is_even; // 记录当前状态是否合法
    }
    f[0][0] = 1; // 初始化的方案数
    for (int i = 1; i <= n; i++) // 每一行
        for (int j = 0; j < (1 << m); j++) { // 每一列
            f[i][j] = 0;
            for (int k = 0; k < (1 << m); k++)
                if (!(j & k) and state[j | k]) // 定位到所有的 1
                    f[i][j] += f[i - 1][k];
        }
    cout << f[n][0] << endl;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    while (cin >> n >> m && n) solve(n, m);
    return 0;
}
