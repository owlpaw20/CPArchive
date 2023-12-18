#include <iostream>

#define endl '\n'

using namespace std;

const int N = 210;
const int INF = 0x7FFFFFFF;

int n, a[N], f[N][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i + n] = a[i];
    }

    for (int i = 3; i <= n + 1; i++)
        for (int j = 1; j + i - 1 <= n * 2; j++) {
            int r = i + j - 1;
            for (int k = j + 1; k < r; k++)
                f[j][r] = max(f[j][r], f[j][k] + f[k][r] + a[j] * a[k] * a[r]);
        }

    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, f[i][i + n]);

    cout << ans << endl;
    fflush(stdout);
    return 0;
}
