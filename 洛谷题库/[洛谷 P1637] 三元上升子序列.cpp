#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_map>

#define endl '\n'

using namespace std;
using Long = long long;

const Long N = 3e4 + 10;

Long n, pos, a[N], t[N], c[N];
Long idx, Left[N], Right[N];
unordered_map<Long, int> disc;

Long lowbit(Long x) { return x & -x; }
void increase(Long x, Long delta) {
    for (Long i = x; i <= n; i += lowbit(i))
        c[i] += delta;
}
Long query(Long x) {
    Long ret = 0;
    for (Long i = x; i; i -= lowbit(i))
        ret += c[i];
    return ret;
}
int discrete(Long x) {
    return lower_bound(t + 1, t + pos + 1, x) - t;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    memcpy(t, a, sizeof a);
    sort(t + 1, t + n + 1);
    pos = unique(t + 1, t + n + 1) - (t + 1);
    for (int i = 1; i <= n; i++) {
        increase(discrete(a[i]), 1ll);
        Left[i] = query(discrete(a[i]) - 1);
    }

    memset(c, 0, sizeof c);
    for (Long i = n; i > 0; i--) {
        increase(discrete(a[i]), 1ll);
        Right[i] = n - i + 1 - query(discrete(a[i]));
    }

    Long ans = 0;
    for (int i = 1; i <= n; i++)
        ans += Left[i] * Right[i];

    cout << ans << endl;
    fflush(stdout);
    return 0;
}
