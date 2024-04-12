#include <iostream>

#define endl '\n'

using namespace std;

const int N = 2e2 + 10;
const int INF = 0x7FFFFFFF;

int n, a[N], f[N][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i], a[i + n] = a[i];  // 因为珠子是连续的，所以断环为链

    for (int i = 3; i <= n + 1; i++)                // 枚举项链的长度
        for (int j = 1; j + i - 1 <= n * 2; j++) {  // 枚举项链的起点
            int r = i + j - 1;                      // 和终点
            for (int k = j + 1; k < r; k++)         // 迭代求当前方案的最大价值
                f[j][r] = max(f[j][r], f[j][k] + f[k][r] + a[j] * a[k] * a[r]);
        }

    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, f[i][i + n]);  // 求以每一颗珠子为起点的项链方案的最大价值

    cout << ans << endl;
    fflush(stdout);
    return 0;
}
