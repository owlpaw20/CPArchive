#include <iostream>
using namespace std;
using i64 = long long;

const int N = 1e5 + 5;

int n, m;
int tr[N];

i64 lowbit(i64 x) { return x & (-x); }
void update(i64 x, i64 delta) {
    for (i64 i = x; i <= n; i += lowbit(i))
        tr[i] += delta;
}
i64 query(i64 x) {
    i64 ret = 0;
    for (i64 i = x; i; i -= lowbit(i))
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
