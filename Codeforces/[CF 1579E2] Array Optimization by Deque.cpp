#pragma GCC optimize("O2,unroll-loops")

#include <climits>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

// 本题卡 unordered_map，用 map 或 pb_ds 可过

#define endl '\n'

using namespace std;
using namespace __gnu_pbds;
using i64 = long long;
using PII = pair<i64, i64>;

const int N = 2e5 + 5;

struct Fenwick {
    i64 tr[N];
    int n;

    i64 lowbit(int x) {
        return x & -x;
    }
    void reset() {
        memset(tr, 0, sizeof tr);
    }

    i64 query(int x) {
        int ret = 0;
        for (int i = x; i; i -= lowbit(i))
            ret += tr[i];
        return ret;
    }

    void update(int x, i64 val) {
        for (int i = x; i <= n; i += lowbit(i))
            tr[i] += val;
    }
};

i64 idx;
PII a[N];
i64 b[N];
Fenwick tr;
gp_hash_table<i64, i64> disc;
auto cmp = [](PII x, PII y) {
    return x.second < y.second;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        idx = 0;
        tr.reset();
        disc.clear();

        int n;
        cin >> n;
        tr.n = n + 5;
        a[0].second = LONG_LONG_MAX;

        for (int i = 1; i <= n; i++)
            cin >> a[i].first, a[i].second = i;

        sort(a + 1, a + n + 1);

        for (int i = 1; i <= n; i++)
            if (a[i].second != a[i - 1].second)
                disc[a[i].first] = ++idx;

        sort(a + 1, a + n + 1, cmp);

        for (int i = 1; i <= n; i++)
            b[i] = disc[a[i].first];

        i64 cnt = 0;
        for (int i = 1; i <= n; i++) {
            cnt += min(tr.query(n) - tr.query(b[i]), tr.query(b[i] - 1));
            tr.update(b[i], 1);
        }

        cout << cnt << endl;
    }

    fflush(stdout);
    return 0;
}
