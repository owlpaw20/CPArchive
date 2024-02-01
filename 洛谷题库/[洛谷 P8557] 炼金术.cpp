#include <iostream>

#define endl '\n'

using namespace std;

const int MOD = 998244353;

int n, k;

int power(int b, int e, int m = MOD) {
    using lng = long long;
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

    cin >> n >> k;

    cout << power(power(2, k) - 1, n) << endl;

    return fflush(stdout), 0;
}
