#include <iostream>

#define endl '\n'

using namespace std;
using lng = long long;

const int N = 1e3 + 10;
const int MOD = 1e4 + 7;

int f[N][N];
int coeff_x, coeff_y;
int exp_p, exp_x, exp_y;

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

    cin >> coeff_x >> coeff_y;
    cin >> exp_p >> exp_x >> exp_y;

    f[1][1] = 1;
    exp_p++;

    for (int i = 2; i <= exp_p; i++)
        for (int j = 1; j <= i; j++)
            f[i][j] = (f[i - 1][j] + f[i - 1][j - 1]) % MOD;

    int multiplier = (lng)power(coeff_x, exp_x) * power(coeff_y, exp_y) % MOD;

    cout << (lng)f[exp_p][exp_y + 1] * multiplier % MOD << endl;
    fflush(stdout);
    return 0;
}
