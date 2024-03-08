#include <set>
#include <iostream>
#include <unordered_map>
using namespace std;
using i64 = long long;

int T = 10;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    while (T--) {
        unordered_map<int, int> arrive, leave;
        set<int> event;
        int l, r, n;
        cin >> l >> r >> n;
        event.insert(l), event.insert(r);
        for (int i = 1; i <= n; i++) {
            int x, y;
            cin >> x >> y;
            event.insert(x);
            event.insert(y);
            arrive[x]++;
            leave[y]++;
        }
        int cnt = 0, mx = 0, mn = n;
        for (int i : event) {
            cnt += arrive[i];
            if (l <= i && i <= r)
                mx = max(mx, cnt);
            cnt -= leave[i];
            if (l <= i && i < r)
                mn = min(mn, cnt);
        }
        cout << mn << " " << mx << endl;
    }
    return 0;
}
