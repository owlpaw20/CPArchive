#include <iostream>
using namespace std;
using lng = long long;

const int N = 1e5 + 10;
lng n, k, act[N];

lng check(lng x) {
    lng prog(0ll), cnt(0ll);
    for (int i = 1; i <= n; i++) {
        prog += act[i];
        if (prog < 0ll) prog = 0ll;
        if (prog >= x) prog = 0ll, cnt++;
    }
    return cnt;
}

lng lower_bound() {
    lng l(1ll), r(1e18), ret(-1ll);
    while (l <= r) {
        lng mid = (l + r) >> 1;
        if (check(mid) <= k) {
            r = mid - 1;
            if (check(mid) == k) ret = mid;
        } else
            l = mid + 1;
    }
    return ret;
}

lng upper_bound() {
    lng l(1ll), r(1e18), ret(-1ll);
    while (l <= r) {
        lng mid = (l + r) >> 1;
        if (check(mid) >= k) {
            l = mid + 1;
            if (check(mid) == k) ret = mid;
        } else
            r = mid - 1;
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> act[i];
    lng lb = lower_bound(), rb = upper_bound();
    if (lb == -1ll || rb == -1ll)
        cout << -1 << endl;
    else
        cout << lb << " " << rb << endl;
    return 0;
}
