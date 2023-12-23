#include <iostream>
using namespace std;
using lng = long long;

const int N = 3e5 + 10;
const lng LONGINF = 0x7FFFFFFFFFFFFFFF;

lng n, m;
lng a[N], b[N];

lng ceil(lng a, lng b) {
    if (a % b == 0LL) return a / b;
    return a / b + 1;
}

bool check(lng x) {
    lng cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] < b[i])
            cnt += ceil(x, b[i]);  // 能自学就全自学
        else if (m * a[i] >= x)
            cnt += ceil(x, a[i]);  // 上课能上完就全上课
        else
            cnt += m + ceil(x - m * a[i], b[i]);  // 上课上不完就用自习来补
        if (cnt > n * m) return false;            // 一个星期的课都不够Bitaro上的
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        a[i] = max(a[i], b[i]);
    }
    lng l = 0, r = LONGINF, ans = 0;
    while (l <= r) {
        lng mid = (l + r) >> 1;
        if (check(mid)) {
            ans = mid;
            l = mid + 1;
        } else
            r = mid - 1;
    }
    cout << ans << endl;
    return 0;
}
