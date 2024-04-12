#include <iostream>

#define endl '\n'

using namespace std;

const int N = 5e4 + 86;

int l, n, m, ll, rr, mid, ans, dis[N];

bool check(int mid) {
    int cnt = 0, index = 0, now = 0;
    while (index < n + 1) {
        index++;
        if (dis[index] - dis[now] < mid)
            cnt++;
        else
            now = index;
    }
    if (cnt > m) return 0;
    return 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> l >> n >> m;
    for (int i = 1; i <= n; i++) cin >> dis[i];

    dis[n + 1] = l;
    ll = 1, rr = l;

    while (ll <= rr) {
        mid = (ll + rr) >> 1;
        if (check(mid)) {
            ans = mid;
            ll = mid + 1;
        } else
            rr = mid - 1;
    }

    cout << ans << endl;
    fflush(stdout);
    return 0;
}
