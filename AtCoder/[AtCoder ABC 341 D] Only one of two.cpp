#include <numeric>
#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;

i64 n, m, K;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> K;

    i64 LCM = lcm(n, m);
    auto check = [&](i64 x) {
        return x / n + x / m - 2 * (x / LCM) < K;
    };

    i64 l = 0, r = 2e18;

    while (l < r) {
        i64 mid = (l + r) >> 1;
        if (check(mid))
            l = mid + 1;
        else
            r = mid;
    }

    cout << r << endl;
    return fflush(stdout), 0;
}
