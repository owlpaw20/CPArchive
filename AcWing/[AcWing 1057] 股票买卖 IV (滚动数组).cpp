#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e5 + 5;
const int M = 1e2 + 5;

int n, K;
int a[N], f[M][2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(f, 0xCF, sizeof f);
    f[0][0] = 0;

    cin >> n >> K;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    for (int i = 1; i <= n; i++) {
        // f[0][0] = f[0][0];
        f[0][1] = max(f[0][1], f[0][0] - a[i]);
        for (int j = 1; j <= K; j++) {
            f[j][1] = max(f[j][1], f[j][0] - a[i]);
            f[j][0] = max(f[j][0], f[j - 1][1] + a[i]);
        }
    }

    int ans = 0;
    for (int i = 0; i <= K; i++)
        ans = max(ans, f[i][0]);

    cout << ans << endl;
    fflush(stdout);
    return 0;
}
