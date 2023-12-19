#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e3 + 10;

int n;
int h[N];
int f[N], g[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> h[i];

    // 最长上升子序列
    for (int i = 1; i <= n; i++) {
        f[i] = 1;
        for (int j = 1; j < i; j++)
            if (h[j] < h[i])
                f[i] = max(f[i], f[j] + 1);
    }

    // 最长下降子序列
    for (int i = n; i >= 1; i--) {
        g[i] = 1;
        for (int j = n; j > i; j--)
            if (h[j] < h[i])
                g[i] = max(g[i], g[j] + 1);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(f[i] + g[i] - 1, ans);

    cout << ans << endl;
    fflush(stdout);
    return 0;
}
