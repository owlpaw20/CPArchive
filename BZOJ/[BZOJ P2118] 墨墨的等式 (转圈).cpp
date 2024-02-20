#include <cstring>
#include <numeric>
#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;
using lng = long long;

const int N = 5e5 + 5;

int n, a[N];
lng l, r, f[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> l >> r;

    int j = 0;
    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        if (x) a[++j] = x;
    }

    n = j;
    sort(a + 1, a + n + 1);

    memset(f, 0x3F, sizeof f);
    f[0] = 0;

    int mod = a[1];

    for (int i = 2; i <= n; i++)
        for (int j = 0, lmt = gcd(a[i], mod); j < lmt; j++)
            for (int k = j, r = 0, p; r < 2; r += (k == j))
                p = (k + a[i]) % mod, f[p] = min(f[p], f[k] + a[i]), k = p;

    lng ans = 0;

    for (int i = 0; i < a[1]; i++) {
        if (r >= f[i]) ans += max(0LL, (r - f[i]) / a[1] + 1);
        if (l > f[i]) ans -= max(0LL, (l - 1 - f[i]) / a[1] + 1);
    }

    cout << ans << endl;
    return fflush(stdout), 0;
}
