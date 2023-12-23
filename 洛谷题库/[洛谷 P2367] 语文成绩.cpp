#include <vector>
#include <climits>
#include <iostream>
using namespace std;

int n, p;
vector<int> a;
vector<int> d;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> p;
    a.resize(n + 2);
    d.resize(n + 2);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        d[i] = a[i] - a[i - 1];
    }

    while (p--) {
        int l, r, x;
        cin >> l >> r >> x;
        d[l] += x;
        d[r + 1] -= x;
    }

    int ans = INT_MAX;
    for (int i = 1; i <= n; i++) {
        a[i] = a[i - 1] + d[i];
        ans = min(ans, a[i]);
    }

    cout << ans << endl;
    return 0;
}
