#include <iostream>
#include <algorithm>  // __gcd()

#define endl '\n'

using namespace std;
using i64 = long long;

const int N = 3e2 + 5;

int n, m;
int flag[N][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 1; i <= 300; i++)
        for (int j = 1; j <= 300; j++)
            flag[i][j] = __gcd(i, j);

    while (cin >> n >> m, n || m) {
        if (n > m) swap(n, m);

        i64 ans = 0;

        for (int i = 1; i < n; i++)
            for (int j = 1; j < m; j++) {
                if (flag[i][j] > 2) continue;

                int same_slope = (n - i) * (m - j);

                if (flag[i][j] == 1) ans += same_slope;
                else ans -= same_slope;
            }

        cout << ans * 2 << endl;
    }

    return fflush(stdout), 0;
}
