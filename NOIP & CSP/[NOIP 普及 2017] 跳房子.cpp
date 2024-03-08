#include <cstring>
#include <iostream>

using namespace std;
using i64 = long long;

const int N = 500000 + 10;
const i64 NINF = 0xcfcfcfcfcfcfcfcf;

int n, d, k;
i64 x[N], s[N], f[N];

bool check(i64 g) {
    for (int i = 1; i <= n; i++) f[i] = NINF;
    f[0] = 0;
    i64 l = d - g, r = d + g;
    if (l <= 0) l = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = i - 1; ~j; j--)
            if (l <= x[i] - x[j] && x[i] - x[j] <= r)
                f[i] = max(f[i], f[j] + s[i]);
            else if (x[i] - x[j] > r)
                break;
        if (f[i] >= k)
            return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> d >> k;
    for (int i = 1; i <= n; i++)
        cin >> x[i] >> s[i];

    int l = 0, r = 1001;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }

    if (l == 1001)
        return (cout << -1 << endl && 0);
    cout << l << endl;
    return 0;
}
