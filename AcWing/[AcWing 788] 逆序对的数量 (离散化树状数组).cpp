#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
using i64 = long long;

const int N = 1e5 + 10;

int n, a[N];
i64 ans = 0;
vector<int> b;

int find(int x) {
    return lower_bound(b.begin(), b.end(), x) - b.begin() + 1;
}

struct Fenwick {
    int tr[N];
    int lowbit(int x) {
        return x & -x;
    }
    int query(int x) {
        int ret = 0;
        for (int i = x; i; i -= lowbit(i))
            ret += tr[i];
        return ret;
    }
    void update(int x, int delta = 1) {
        for (int i = x; i <= N; i += lowbit(i))
            tr[i] += delta;
    }
    Fenwick() {
        memset(tr, 0, sizeof tr);
    }
} tree;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i], b.push_back(a[i]);
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    for (int i = 1; i <= n; i++) {
        int Hash = find(a[i]);
        tree.update(Hash);
        ans += tree.query(n) - tree.query(Hash);
    }
    cout << ans << endl;
    return 0;
}
