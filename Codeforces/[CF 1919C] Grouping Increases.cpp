#include <vector>
#include <climits>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 2e5 + 10;

void solve() {
    int n;
    cin >> n;

    int ans = 0;
    vector<int> s{INT_MAX}, t{INT_MAX};

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;

        if (x <= s.back()) s.push_back(x);
        else if (x > t.back()) s.push_back(x), ans++;
        else t.push_back(x);

        if (s.back() > t.back()) swap(s, t);
    }

    cout << ans << endl;
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
