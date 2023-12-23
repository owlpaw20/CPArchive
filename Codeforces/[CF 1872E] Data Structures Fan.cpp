#include <string>
#include <cstring>
#include <iostream>
using namespace std;

const int N = 1e5 + 10;

int T, a[N], p[N];

void solve() {
    int n, q;
    string s;
    memset(a, 0, sizeof a);
    memset(p, 0, sizeof p);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        p[i] = p[i - 1] ^ a[i];
    }
    cin >> s;
    int sum0(0), sum1(0);
    for (int i = 0; i < n; i++)
        if (s[i] == '0')
            sum0 ^= a[i + 1];
        else if (s[i] == '1')
            sum1 ^= a[i + 1];
    cin >> q;
    while (q--) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int l, r;
            cin >> l >> r;
            sum0 ^= p[r] ^ p[l - 1];
            sum1 ^= p[r] ^ p[l - 1];
        } else {
            int x;
            cin >> x;
            if (x == 0)
                cout << sum0 << " ";
            else if (x == 1)
                cout << sum1 << " ";
        }
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> T;
    while (T--)
        solve();
    return 0;
}
