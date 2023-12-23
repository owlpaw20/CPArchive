#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
using lng = long long;

const int pow2[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};

int n;
lng k, ans = 0;

lng fast_exp(lng a, int b) {
    lng ret = 1;
    while (b) {
        if (b & 1) ret = ret * a;
        a = a * a;
        b >>= 1;
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> k >> n;
    for (int i = 9; i >= 0; i--) {
        if (pow2[i] > n) continue;
        n -= pow2[i];
        ans += (lng)fast_exp(k, i);
    }
    cout << ans << endl;
    return 0;
}
