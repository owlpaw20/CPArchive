#include <cstring>
#include <iostream>

using namespace std;
using lng = long long;

const int N = 2e5 + 10;
const int INF = 0x7fffffff;
const lng LINF = 0x7fffffffffffffff;

int n, m;
int w[N], v[N];
int p[N], q[N];
lng pn[N], pv[N];
lng s, ans = LINF;

lng absolute(lng x) { return (x < 0 ? -x : x); }

bool check(int x) {
    lng y = 0;
    for (int i = 1; i <= n; i++) {
        pn[i] = pn[i - 1] + (w[i] >= x ? 1 : 0);
        pv[i] = pv[i - 1] + (w[i] >= x ? v[i] : 0);
    }

    for (int i = 1; i <= m; i++)
        y += (pn[q[i]] - pn[p[i] - 1]) * (pv[q[i]] - pv[p[i] - 1]);

    lng delta = absolute(y - s);
    ans = min(ans, delta);

    if (y > s) return true;
    else if (y == s) {
        cout << 0 << endl;
        exit(0);
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> s;
    for (int i = 1; i <= n; i++) cin >> w[i] >> v[i];
    for (int i = 1; i <= m; i++) cin >> p[i] >> q[i];

    int l = 0, r = 1e6;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(mid)) l = mid + 1;
        else r = mid;
    }

    cout << ans << endl;
    return 0;
}
