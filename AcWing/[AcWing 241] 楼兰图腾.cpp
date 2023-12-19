#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;
using Long = long long;

const int N = 2e5 + 10;

Long n, a[N];
Long hi[N], lo[N], tr[N];
Long ans1, ans2;

Long lowbit(Long x) { return x & -x; }

void add(Long x, Long delta) {
    for (Long i = x; i <= n; i += lowbit(i))
        tr[i] += delta;
}

Long sum(Long x) {
    Long ret = 0;
    for (Long i = x; i; i -= lowbit(i))
        ret += tr[i];
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    for (int i = 1; i <= n; i++) {
        int t = a[i];
        hi[i] = sum(n) - sum(t);
        lo[i] = sum(t - 1);
        add(t, 1);
    }

    memset(tr, 0, sizeof tr);

    for (int i = n; i >= 1; i--) {
        int t = a[i];
        ans1 += hi[i] * (sum(n) - sum(t));
        ans2 += lo[i] * (sum(t - 1));
        add(t, 1);
    }

    cout << ans1 << " " << ans2 << endl;
    fflush(stdout);
    return 0;
}
