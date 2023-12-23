#include <iostream>
using namespace std;
using lng = long long;

const int N = 1e5 + 10;

lng n, a[N], ans, cnt;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] += a[i - 1];
    }
    if (a[n] % 3) return (cout << 0 << endl) && 0;
    lng part = a[n] / 3;
    for (int i = 1; i < n; i++) {
        if (a[i] == 2 * part) ans += cnt;
        if (a[i] == part) cnt++;
    }
    cout << ans << endl;
    return 0;
}
