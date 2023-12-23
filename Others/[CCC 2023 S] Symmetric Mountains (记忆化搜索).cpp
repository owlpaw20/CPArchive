#include <cstring>
#include <iostream>
#define endl '\n'

using namespace std;

const int N = 5e3 + 5;
const int INF = 0x7FFFFFFF;

int n;
int h[N];
int f[N][N];

int calc(int l, int r) {  // 记搜
    if (l > r) return 0;
    if (f[l][r] != -1) return f[l][r];
    return f[l][r] = abs(h[l] - h[r]) + calc(l + 1, r - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(f, -1, sizeof f);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> h[i];

    for (int i = 1; i <= n; i++) {  // 枚举长度
        int ans = INF;
        for (int j = 1; j + i - 1 <= n; j++)     // 枚举起点
            ans = min(ans, calc(j, j + i - 1));  // 计算不对称分数
        cout << ans << ' ';
    }

    cout.put('\n');
    fflush(stdout);
    return 0;
}
