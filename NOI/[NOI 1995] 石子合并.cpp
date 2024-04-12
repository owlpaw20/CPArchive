#include <climits>
#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 4e2 + 5;

int n;
int a[N], pre[N];
int f[N][N], g[N][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(f, 0x3F, sizeof f);
    memset(g, 0xCF, sizeof g);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i], a[i + n] = a[i];
    for (int i = 1; i <= (n << 1); i++)
        pre[i] = pre[i - 1] + a[i];

    for (int len = 1; len <= n; len++)
        for (int l = 1; l + len - 1 <= (n << 1); l++) {
            int r = l + len - 1;
            if (l == r)
                f[l][r] = g[l][r] = 0;
            else {
                int range_sum = pre[r] - pre[l - 1];
                for (int mid = l; mid < r; mid++) {
                    f[l][r] = min(f[l][r], f[l][mid] + f[mid + 1][r] + range_sum);
                    g[l][r] = max(g[l][r], g[l][mid] + g[mid + 1][r] + range_sum);
                }
            }
        }

    int ans1 = INT_MAX, ans2 = INT_MIN;
    for (int l = 1; l <= n; l++) {
        int r = l + n - 1;
        ans1 = min(ans1, f[l][r]);
        ans2 = max(ans2, g[l][r]);
    }

    cout << ans1 << endl
         << ans2 << endl;
    fflush(stdout);
    return 0;
}
