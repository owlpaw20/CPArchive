#pragma GCC optimize("O2,unroll-loops")
#include <iostream>

using namespace std;
using i64 = long long;

const int N = 1e5 + 10;

int n, a[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    i64 sumP = 0, sumN = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (i > 1) {
            int d = a[i] - a[i - 1];
            if (d >= 0)
                sumP += d;
            else
                sumN -= d;
        }
    }

    cout << max(sumP, sumN) << '\n';
    cout << abs(sumP - sumN) + 1 << '\n';
    fflush(stdout);
    return 0;
}
