#include <cmath>
#include <iostream>

#define endl '\n'

using namespace std;
using lng = long long;

int T;

lng power(lng b, int e) {
    lng ret = 1;
    while (e) {
        if (e & 1) ret = ret * b;
        b = b * b;
        e >>= 1;
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        lng n;
        cin >> n;
        lng ans = 1LL << (int)ceil(log2(n));
        cout << ans << ' ';
        while (n % 2 == 0)
            n >>= 1, ans >>= 1;
        cout << log2(ans) << endl;
    }

    fflush(stdout);
    return 0;
}
