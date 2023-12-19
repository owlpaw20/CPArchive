#include <iostream>

#define endl '\n'

using namespace std;
using lng = long long;

const int MOD = 1e5 + 3;

lng m, n;

lng power(lng b, lng e, lng m = MOD) {
    lng ret = 1;
    while (e) {
        if (e & 1) ret = ret * b % m;
        b = b * b % m;
        e >>= 1;
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> n;
    cout << (power(m, n) - m * power(m - 1, n - 1) % MOD + MOD) % MOD << endl;

    fflush(stdout);
    return 0;
}
