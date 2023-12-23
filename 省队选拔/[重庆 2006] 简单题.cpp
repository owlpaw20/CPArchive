#include <iostream>
using namespace std;
using lng = long long;

const int N = 1e5 + 5;

int n, m;
int tr[N];

lng lowbit(lng x) { return x & (-x); }
void update(lng x, lng delta) {
    for (lng i = x; i <= n; i += lowbit(i))
        tr[i] += delta;
}
lng query(lng x) {
    lng ret = 0;
    for (lng i = x; i; i -= lowbit(i))
        ret += tr[i];
    return ret % 2LL;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    while (m--) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int l, r;
            cin >> l >> r;
            update(l, 1), update(r + 1, -1);
        } else {
            int idx;
            cin >> idx;
            cout << query(idx) << endl;
        }
    }
    return 0;
}
