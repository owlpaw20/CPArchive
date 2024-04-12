#include <cmath>
#include <climits>
#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;
using flt = double;
using PFF = pair<flt, flt>;

const int N = 20;
const flt EPS = 1e-10;
const int INF = INT_MIN;
const PFF NaN = PFF(INF, INF);

PFF pigs[N];
int f[1 << N];
int path[N][N];

int cmp(flt x, flt y) {
    if (fabs(x - y) < EPS) return false;
    return (x < y ? -1 : 1);
}

PFF projectile(flt x1, flt y1, flt x2, flt y2) {
    flt a = (y1 / x1 - y2 / x2) / (x1 - x2);
    flt b = y1 / x1 - a * x1;
    return PFF(a, b);
}

void solve() {
    memset(path, 0, sizeof path);
    memset(f, 0x3F, sizeof f);

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> pigs[i].first >> pigs[i].second;

    for (int i = 0; i < n; i++) {
        path[i][i] = 1 << i;  // 初始化当前小猪被覆盖的状态
        auto [x1, y1] = pigs[i];

        for (int j = 0; j < n; j++) {
            auto [x2, y2] = pigs[j];
            if (cmp(x1, x2) == 0) continue;  // 如果选到的小猪的横坐标相同，则抛物线不存在

            auto [a, b] = projectile(x1, y1, x2, y2);  // 获取通过两只小猪确定的抛物线的系数
            if (cmp(a, 0) >= 0) continue;              // 如果不成二次函数或者开口向上则抛物线不合法

            int state = 0;
            for (int k = 0; k < n; k++) {
                auto [x, y] = pigs[k];               // 看当前抛物线还能不能覆盖其他小猪
                if (cmp(a * x * x + b * x, y) == 0)  // 如果可以就更新状态
                    state |= 1 << k;
            }

            path[i][j] = state;  // 保存当前抛物线的状态
        }
    }

    f[0] = 0;  // f[i] 表示当前已经覆盖的列是 i 时的最小行数
    for (int i = 0; (i + 1) < (1 << n); i++) {
        int x = 0;
        for (int j = 0; j < n; j++)
            if (((i >> j) & 1) == 0) {  // 找到当前仍未被覆盖的列 X
                x = j;
                break;
            }
        for (int j = 0; j < n; j++)
            f[i | path[x][j]] = min(f[i | path[x][j]], f[i] + 1);  // 并用所有能覆盖 X 的列进行覆盖
    }

    cout << f[(1 << n) - 1] << endl;  // 找到完全覆盖的情况的最小答案
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) solve();

    fflush(stdout);
    return 0;
}
