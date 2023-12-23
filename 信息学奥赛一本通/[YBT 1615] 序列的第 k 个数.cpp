#include <iostream>
#define endl '\n'

using namespace std;
using lng = long long;

const int MOD = 200907;

int T;

int power(int b, int e, int m = MOD) {
    int ret = 1;
    while (e) {
        if (e & 1) ret = (lng)ret * b % m;
        b = (lng)b * b % m;
        e >>= 1;
    }
    return ret % m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        int p[3], K;
        cin >> p[0] >> p[1] >> p[2] >> K;
        if (p[2] - p[1] == p[1] - p[0]) {
            int delta = p[1] - p[0];
            cout << ((lng)delta * (K - 1) % MOD + p[0]) % MOD << endl;
        } else {
            int delta = p[1] / p[0];
            cout << (lng)p[0] * power(delta, K - 1) % MOD << endl;
        }
    }

    fflush(stdout);
    return 0;
}
