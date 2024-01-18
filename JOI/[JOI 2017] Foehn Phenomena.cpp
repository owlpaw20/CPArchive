#include <iostream>

using namespace std;
using lng = long long;

const int N = 2e5 + 10;

lng n, q, s, t, ans;
lng pre, tmp, d[N];

lng alt(int x) {
    if (d[x] > 0) return -d[x] * s;
    return -d[x] * t;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q >> s >> t >> pre;

    for (int i = 1; i <= n; i++) {
        cin >> tmp;
        d[i] = tmp - pre;
        pre = tmp;
        ans += alt(i);
    }

    while (q--) {
        int l, r, x;
        cin >> l >> r >> x;
        ans -= alt(l);
        d[l] += x;
        ans += alt(l);
        if (r < n) {
            ans -= alt(r + 1);
            d[r + 1] -= x;
            ans += alt(r + 1);
        }
        cout << ans << endl;
    }

    return 0;
}
