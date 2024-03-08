#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;

const int N = 2e5 + 5;

int n;
i64 a[N], s[N], t[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i < n; i++) cin >> s[i] >> t[i];

    for (int i = 1; i < n; i++) {
        i64 k = a[i] / s[i];
        a[i + 1] += t[i] * k;
    }

    cout << a[n] << endl;
    return fflush(stdout), 0;
}
