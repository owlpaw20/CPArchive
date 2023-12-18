#include <iostream>

#define endl '\n'

using namespace std;
using lng = long long;

int fast_exp(int a, int b, int p) {
    int ret = 1;
    while (b) {
        if (b & 1) ret = (lng)ret * a % p;
        a = (lng)a * a % p;
        b >>= 1;
    }
    return ret;
}

int n, m, K, x;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> K >> x;
    cout << (x + (lng)fast_exp(10, K, n) * m % n) % n << endl;
    fflush(stdout);
    return 0;
}
