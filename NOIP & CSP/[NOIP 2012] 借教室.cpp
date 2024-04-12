#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;

const int N = 1e6 + 10;

int n, m, sz, v[N];
i64 dff[N], sum[N];
int st[N], ed[N], cnt[N];

bool check(int x) {
    memset(dff, 0, sz);
    memset(sum, 0, sz);

    for (int i = 1; i <= x; i++)
        dff[st[i]] += cnt[i], dff[ed[i] + 1] -= cnt[i];

    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + dff[i];
        if (sum[i] > v[i])
            return false;
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    sz = n * 8 + 40;
    for (int i = 1; i <= n; i++) cin >> v[i];
    for (int i = 1; i <= m; i++) cin >> cnt[i] >> st[i] >> ed[i];

    if (check(m)) return (cout << 0 << endl) && 0;
    cout << -1 << endl;

    int l = 1, r = m;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(mid))
            l = mid + 1;
        else
            r = mid;
    }

    cout << r << endl;
    fflush(stdout);
    return 0;
}
