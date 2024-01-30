#include <numeric>
#include <iostream>
#include <unordered_set>

#define endl '\n'

using namespace std;

void solve() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;

    unordered_set<int> ans;
    for (int i = 1; i * i <= d; i++)
        if (d % i == 0) {
            int j = d / i;
            if (i % b == 0 && gcd(i / b, a / b) == 1 && gcd(d / c, d / i) == 1) ans.insert(i);
            if (j % b == 0 && gcd(j / b, a / b) == 1 && gcd(d / c, d / j) == 1) ans.insert(j);
        }

    cout << ans.size() << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) solve();

    fflush(stdout);
    return 0;
}
