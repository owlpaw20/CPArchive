#include <cstring>
#include <iostream>

using namespace std;

const int N = 110;
const int M = 15;
const int INF = 0x3f3f3f3f;

int n, m, a[N], p[N];
int mx[N][N][M], mn[N][N][M];

int mod(int x) { return (x % 10 + 10) % 10; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i + n] = a[i];
    }

    for (int i = 1; i <= 2 * n; i++)
        p[i] = p[i - 1] + a[i];

    memset(mx, -INF, sizeof mx);
    memset(mn, INF, sizeof mn);

    for (int len = 1; len <= n; len++)
        for (int l = 1; l + len - 1 <= 2 * n; l++) {
            int r = l + len - 1;
            mx[l][r][1] = mn[l][r][1] = mod(p[r] - p[l - 1]);
            for (int k = 2; k <= m; k++)
                for (int j = l + k - 2; j < r; j++) {
                    mx[l][r][k] = max(mx[l][r][k], mx[l][j][k - 1] * mod(p[r] - p[j]));
                    mn[l][r][k] = min(mn[l][r][k], mn[l][j][k - 1] * mod(p[r] - p[j]));
                }
        }

    int mxv = -INF, mnv = INF;
    for (int i = 1; i <= n; i++) {
        mxv = max(mxv, mx[i][i + n - 1][m]);
        mnv = min(mnv, mn[i][i + n - 1][m]);
    }

    cout << mnv << endl
         << mxv << endl;
    return 0;
}
