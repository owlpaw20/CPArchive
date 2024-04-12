#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;

const int N = 1e6 + 86;
int n, m, h[N];
long long l, r, mid;

bool check(long long mh) {
    long long cnt = 0;
    for (int i = 1; i <= n; i++)
        if (mh < h[i])
            cnt += h[i] - mh;
    if (cnt >= m) return 1;
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
        r = max(r, (long long)h[i]);
    }

    sort(h + 1, h + n + 1);

    l = 1;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (check(mid))
            l = mid + 1;
        else
            r = mid - 1;
    }

    cout << l - 1 << endl;
    fflush(stdout);
    return 0;
}
