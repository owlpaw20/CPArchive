#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;

const int MOD = 1e5 + 3;

i64 m, n;

i64 power(i64 b, i64 e, i64 m = MOD) {
    i64 ret = 1;
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
