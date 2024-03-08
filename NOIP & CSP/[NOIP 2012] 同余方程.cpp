#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;

int a, b;

void extend_gcd(i64 a, i64 b, i64& x, i64& y) {
    if (b == 0) return (void)(x = 1, y = 0);
    extend_gcd(b, a % b, y, x);
    y -= a / b * x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a >> b;

    i64 x, y;
    extend_gcd(a, b, x, y);

    cout << (x % b + b) % b << endl;
    return fflush(stdout), 0;
}
