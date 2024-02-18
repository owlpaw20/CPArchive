#include <numeric>
#include <iostream>

#define endl '\n'

using namespace std;
using lng = long long;

lng n, m, K;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> K;

    lng LCM = lcm(n, m);
    auto check = [&](lng x) { return x / n + x / m - 2 * (x / LCM) < K; };

    lng l = 0, r = 2e18;

    while (l < r) {
        lng mid = (l + r) >> 1;
        if (check(mid)) l = mid + 1;
        else r = mid;
    }

    cout << r << endl;
    return fflush(stdout), 0;
}
