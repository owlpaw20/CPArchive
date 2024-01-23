#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;

const int N = 2e2 + 10;
const int M = N * N * 10;

int n;
int a[N], c[N];
i64 f[M], maxc, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> c[i], maxc += c[i] * a[i];

    f[0] = 1;

    for (int i = 1; i <= n; i++)
        for (int j = maxc; j >= 0; j--)
            for (int k = 0; k <= a[i] && k * c[i] <= j; k++)
                f[j] = max(f[j], f[j - k * c[i]] * k);

    i64 ans = 0;
    while (ans <= maxc && f[ans] < m) ans++;
    cout << ans << endl;

    fflush(stdout);
    return 0;
}
