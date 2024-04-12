#include <climits>
#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;

const int N = 5e3 + 10;

int n, f[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    if (!n) {
        cout << 0 << endl;
        return 0;
    }

    for (int i = 1; i <= n; i++)
        f[i] = INT_MAX - 1;

    f[0] = 0;

    for (int i = 1; i <= n; i++) {
        if (i >= 3) f[i] = min(f[i], f[i - 3] + 1);
        if (i >= 5) f[i] = min(f[i], f[i - 5] + 1);
    }

    if (f[n] == INT_MAX - 1)
        cout << -1 << endl;
    else
        cout << f[n] << endl;
    fflush(stdout);
    return 0;
}
